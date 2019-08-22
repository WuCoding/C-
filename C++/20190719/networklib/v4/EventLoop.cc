#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <assert.h>
#include <sys/eventfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数
EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventFd())//eventfd描述符
, _acceptor(acceptor)
, _eventList(1024)//调用vector的构造函数，将承载监控事件的vector容器初始化为1024大小
, _isLooping(false)
{
	addEpollFdRead(_acceptor.fd());	//监听连接描述符
	addEpollFdRead(_eventfd);	//监听eventfd描述符
}

void EventLoop::loop()
{
	//开始循环查看监控事件
	_isLooping=true;
	while(_isLooping){
		waitEpollFd();
	}
}

void EventLoop::unloop()
{
	//结束监控事件的查看
	if(_isLooping){
		_isLooping=false;//将标志位置为false
	}
}

void EventLoop::runInLoop(Functor && cb)
{
	{
		//上锁
		MutexLockGuard autolock(_mutex);
		//将执行函数压入vector容器中
		_pendingFunctors.push_back(std::move(cb));
	}
	//解锁
	wakeup();//唤醒，向eventfd中的计数器中加数
}

void EventLoop::waitEpollFd()
{
	int nready;
	do{
		nready=epoll_wait(_efd,&*_eventList.begin(),_eventList.size(),5000);//等待事件5000ms
	}while(nready==-1 && errno==EINTR);//防止因中断导致该语句执行失败

	if(nready==-1){
		perror("epoll_wait");
		return;
	}else if(nready==0){//等待超时
		cout<<">> epoll_wait timeout!"<<endl;
	}else{
		//获得已经被唤醒的事件
		if(nready==_eventList.size()){//容器已满，进行扩容
			_eventList.resize(2*nready);
		}

		//遍历已唤醒的描述符
		for(int idx=0;idx!=nready;++idx){
			int fd=_eventList[idx].data.fd;
			if(fd==_acceptor.fd()){//有新的连接请求
				//处理新的链接
				if(_eventList[idx].events & EPOLLIN){
					//监控该描述符的可读事件
					handleNewConnection();
				}
			}else if(fd==_eventfd){//处理eventfd事件
				if(_eventList[idx].events & EPOLLIN){
					handleRead();//执行eventfd的读操作
					cout<<">>before doPendingFunctors()"<<endl;
					//在这里将_pendingFunctors中的函数全部执行
					//，在这里发送数据
					doPendingFunctors();
					cout<<">>after doPendingFunctors()"<<endl;
				}
			}else{
				//有新的消息发送来，处理消息
				if(_eventList[idx].events & EPOLLIN){
					handleMessage(fd);
				}
			}
		}
	}
}

//处理新的链接请求
void EventLoop::handleNewConnection()
{
	//进行数据传输的套接字
	int peerfd=_acceptor.accept();
	//将新的套接字加入到epoll监控中
	addEpollFdRead(peerfd);
	//this指针是EventLoop对象的指针
	TcpConnectionPtr conn(new TcpConnection(peerfd,this));
	//注册回调函数
	conn->setConnectionCallback(_onConnection);
	conn->setMessageCallback(_onMessage);
	conn->setCloseCallback(_onClose);

	//将TcpConnectionPtr指针和它用来进行信息交流的套接字放入到map容器中
	_conns.insert(std::make_pair(peerfd,conn));

	//执行新链接时的回调函数
	conn->handleConnectionCallback();
}

//处理新信息
void EventLoop::handleMessage(int fd)
{
	//判断是否因为对端关闭导致描述符可读
	bool isClosed=isConnectionClosed(fd);
	auto iter=_conns.find(fd);//_conns是一个map容器
	assert(iter!=_conns.end());//运行时断言

	if(!isClosed){//描述符可读不是因对端关闭导致的
		//执行有信息的回调函数
		iter->second->handleMessageCallback();
	}else{//对端关闭
		delEpollFdRead(fd);
		//执行关闭回调函数，iter->second为TcpConnectionPtr指针
		iter->second->handleCloseCallback();
		//从map容器中删除
		_conns.erase(iter);
	}
}

//对eventfd描述符进行读操作
void EventLoop::handleRead()
{
	uint64_t howmany;
	int ret=::read(_eventfd,&howmany,sizeof(howmany));
	if(ret!=sizeof(howmany)){
		perror("read");
	}
}

//对eventfd描述符进行唤醒操作，向计数器中加时间
void EventLoop::wakeup()
{
	uint64_t one=1;
	int ret=::write(_eventfd,&one,sizeof(one));
	if(ret!=sizeof(one)){
		perror("write");
	}
}

//当eventfd可读时执行函数
void EventLoop::doPendingFunctors()
{
	vector<Functor> tmp;
	{
		//上锁
		MutexLockGuard autolock(_mutex);
		//将tmp和_pendingFunctors交换
		tmp.swap(_pendingFunctors);//_pendingFunctors容器变为空
	}
	//解锁
	for(auto & functor: tmp)
	{
		//执行函数
		functor();
	}
}

//判断描述符可读是否是因为对端关闭
bool EventLoop::isConnectionClosed(int fd)
{
	int ret;
	do{
		char buff[1024];
		//复制式读取
		ret=recv(fd,buff,sizeof(buff),MSG_PEEK);
	}while(ret==-1 && errno==EINTR);

	return (ret==0);
}

//创建epoll描述符
int EventLoop::createEpollFd()
{
	int ret=::epoll_create1(0);
	if(ret==-1){
		perror("epoll_create1");
	}
	return ret;
}

//创建eventfd描述符
int EventLoop::createEventFd()
{
	int ret=::eventfd(0,0);
	if(ret==-1){
		perror("eventfd");
	}
	return ret;
}

//将一个描述符的可读事件加入到epoll监控队列中
void EventLoop::addEpollFdRead(int fd)
{
	struct epoll_event evt;
	evt.data.fd=fd;
	evt.events=EPOLLIN;
	int ret=epoll_ctl(_efd,EPOLL_CTL_DEL,fd,&evt);
	if(-1==ret){
		perror("epoll_ctl");
	}
}
}//end of namespace wd
