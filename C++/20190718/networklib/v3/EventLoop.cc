#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数
EventLoop::EventLoop(Acceptor &acceptor)
: _efd(createEpollFd()) //createEpollFd()创建一个epoll描述符
, _acceptor(acceptor)   //acceptor里是一个和服务端的ip和port绑定的监控链接的描述符，和服务端地址
, _eventList(1024)
, _isLooping(false)
{
	//将监控链接的描述符加入epoll监控队列
	addEpollFdRead(_acceptor.fd());
}

//开始循环执行可执行事件
void EventLoop::loop()
{
	_isLooping=true;
	while(_isLooping){
		waitEpollFd();
	}
}

void EventLoop::unloop()
{
	if(_isLooping){//如果已经开始循环了
		_isLooping=false;
	}
}
void EventLoop::waitEpollFd()
{
	//已经就绪的描述符
	int nready;
	do{
		//获得已经就绪的描述符列表
		nready=epoll_wait(_efd,&*_eventList.begin(),_eventList.size(),5000);//等待5000ms
	}while(-1==nready && errno==EINTR);

	if(nready==-1){//执行出错
		perror("epoll_wait");
		return;
	}else if(nready==0){//时间到达，但无描述符就绪
		cout<<">> epoll_wait timeout!"<<endl;
	}else{//正常获得就绪描述符
		if(nready==_eventList.size()){//承就绪描述符的容器容量不够
			//进行扩容
			_eventList.resize(2*nready);
		}

		//遍历就绪的描述符
		for(int idx=0;idx!=nready;++idx){
			//用来保存就绪的描述符
			int fd=_eventList[idx].data.fd;
			if(fd==acceptor.fd()){//有新的链接请求
				if(_eventList[idx].events & EPOLLIN){
					//如果监控的该描述符为是否可读
					handleNewConnection();
				}
			}else{//有新的可读信息
				if(_eventList[idx].events & EPOLLIN)
					//监控的是该描述符的是否可读
					handleMessage(fd);
			}
		}
	}
}

//执行新的链接请求
void EventLoop::handleNewConnection()
{
	//获得新的套接字
	int peerfd=_acceptor.accept();
	//将新的套接字加入到epoll监控队列中
	addEpollFdRead(peerfd);

	//TcpConnection类型中只传入一个描述符，获得该描述符绑定的本地地址和对端地址
	//还有注册的回调函数，对该全双工描述符进行读写操作
	TcpConnectionPtr conn(new TcpConnection(peerfd));
	//对该套接字注册回调函数
	conn->setConnectionCallback(_onConnection);
	conn->setMessageCallback(_onMessage);
	conn->setCloseCallback(_onClose);

	//将该套接字和TcpConnection指针构成键值对，放入容器中
	_conns.insert(std::make_pair(peerfd,conn));
	//执行链接时的回调函数
	conn->handleConnectionCallback();
}

//处理新的信息
void EventLoop::handleMessage(int fd)
{
	//判断是否因为对端关闭导致描述符可读
	bool isClosed=isConnectionClosed(fd);
	auto iter=_conns.find(fd);
	assert(iter!=_conns.end());//运行时断言，括号内为false时，终止操作
	
	if(!isClosed){//对端未关闭
		//执行该描述符的信息可读时的回调函数
		iter->second->handleMessageCallback();
	}else{//对端关闭
		//从epoll监控队列中删除该描述符
		delEpollFdRead(fd);
		//执行关闭描述符时的回调函数
		iter->second->handleCloseCallback();
		//将该键值对从容器中删除
		_conns.erase(iter);
	}
}

//判断对端是否关闭
bool EventLoop::isConnectionClosed(int fd)
{
	int ret;
	do{
		char buff[1024];
		//注意，这里是复制式读取
		ret=recv(fd,buff,sizeof(buff),MSG_PEEK);
	}while(ret==-1 && errno==EINTR);

	//如果ret等于0表示对端关闭
	return (ret==0);
}

//创建一个epoll监控描述符
int EventLoop::createEpollFd()
{
	int ret=::epoll_create1(0);
	if(ret==-1){
		perror("epoll_create1");
	}
	return ret;
}

//将一个描述符的可读事件注册进epoll监控队列中
void EventLoop::addEpollFdRead(int fd)
{
	struct epoll_event evt;
	evt.data.fd=fd;
	evt.events=EPOLLIN;//监控该描述符的是否可读
	int ret=epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&evt);
	if(-1==ret){
		perror("epoll_ctl");
	}
}

//将一个描述符的可读事件从epoll监控队列中删除
void EventLoop::delEpollFdRead(int fd)
{
	struct epoll_event evt;
	evt.data.fd=fd;
	int ret=epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&evt);
	if(-1==ret){
		perror("epoll_ctl");
	}
}
}//end of namespace wd



