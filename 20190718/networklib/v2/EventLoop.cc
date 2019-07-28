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
EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
	addEpollFdRead(_acceptor.fd());
}

void EventLoop::loop()
{
	//开始事件循环
	_isLooping=true;
	
	while(_isLooping){
		waitEpollFd();
	}
}

void EventLoop::unloop()
{
	if()
}

void EventLoop::waitEpollFd()
{
	//已经可以执行的描述符数量
	int nready;
#if 0
等待事件的产生
函数原型：
int epoll_wait(int epfd,struct epoll_event* events,int maxevents,int timeout);
epfd:
	>epoll的句柄
events:
	>从内核得到事件的集合
maxevents:
	>告诉内核这个events有多大，不能大于创建epoll_create()时的size
timeout:
	>超时时间：单位毫秒，0立即返回，-1永久堵塞
返回值：
	>返回需要处理的事件数目，返回0表示已超时
#endif
	do{
		nready=epoll_wait(_efd,&*_eventList.begin(),_eventList.size(),5000);//5000ms的意思
	}while(nready==-1 && errno==EINTR);

	if(nready==-1){
		//epoll_wait函数执行出错
		perror("epoll_wait");
		return;
	}else if(nready==0){
		//没有需要处理的事件，已经超时
		cout<<">>epoll_wait timeout!"<<endl;
	}else{
		//有要处理的事件
		if(nready==_eventList.size()){
			//如果要处理的事件将事件链表装满，则重新扩容
			_eventList.resize(2*nready);
		}
		//依次遍历要处理的事件描述符
		for(int idx=0;idx!=nready;++idx){
			//fd来存储要处理的事件描述符
			int fd=_eventList[idx].data.fd;
			if(fd==_acceptor.fd()){
				//有新的链接请求
				//按位与&，只有两个二进位都为1，结果才为1
				if(_eventList[idx].events & EPOLLIN){
					//表示对应的请求链接描述符可读
					handleNewConnection();
				}
			}else{
				//已连接的socket套接字描述符可读
				if(_eventList[idx].events & EPOLLIN){
					//表示对应的描述符有数据可读
					handleMessage(fd);
				}
			}
		}
	}
}

//对新请求链接的套接字进行处理
void EventLoop::handleNewConnection()
{
	//peerfd新的套接字描述符
	int peerfd=_acceptor.accept();
	//将新的套接字加入到epoll监控中
	addEpollFdRead(peerfd);
	//用该已连接的套接字创建TcpConnection类型的对象
	TcpConnectionPtr conn(new TcpConnection(peerfd));//conn智能指针
	//设置连接的回调函数
	conn->setConnectionCallback(_onConnection);
	//设置处理信息的回调函数
	conn->setMessageCallback(_onMessage);
	//设置关闭套接字的回调函数
	conn->setCloseCallback(_onClose);

	//将套接字和TcpConnction类型的智能指针结对放入容器
	_conns.insert(std::make_pair(peerfd,conn));
	//执行TcpConnection类型的回调函数
	conn->handleConnectionCallback();
}

//对套接字描述符可读的操作
void EventLoop::handleMessage(int fd)
{
	//查看是否因对端关闭导致的套接字可读
	bool isClosed=isConnectionClosed(fd);
	//从容器中找到该套接字的TcpConnection对象智能指针和fd对
	auto iter=_conns.find(fd);
#if 0
assert()
编写代码时，我们总是会做出一些假设，断言就是用于在代码中捕捉这些假设，
可以将断言看作是异常处理的一种高级形式。断言表示为一些布尔表达式，
程序员相信在程序中的某个特定点该表达式值为真。可以在任何时候启用和禁用断言验证，
因此可以在测试时启用断言，而在部署时禁用断言。同样，程序投入运行后，
最终用户在遇到问题时可以重新启用断言。assert是宏，而不是函数
#endif
	//运行时断言，括号中值为false时中断当前操作
	assert(iter!=_conns.end());
	
	if(!isClosed){
		//并非对端关闭导致的套接字可读
		//iter->second为TcpConnection类型智能指针
		//执行信息回调函数
		iter->second->handleMessageCallback();
	}else{//对端关闭
		//将该套接字从epoll监控中删除
		delEpollFdRead(fd);
		//执行该TcpConnection智能指针的关闭回调函数
		iter->second->handleCloseCallback();
		//将该描述符的键值对从容器中删除
		_conns.erase(iter);
	}
}

//判断对端是否关闭
bool EventLoop::isConnectionClosed(int fd)
{
	int ret;
	do{
		char buff[1024];
		//当ret读到的字节数为0，表示对端关闭
		ret=recv(fd,buff,sizeof(buff),MSG_PEEK);
	}while(ret==-1 && errno==EINTR);

	return (ret==0);
}

//创建一个epollfd描述符
int EventLoop::createEpollFd()
{
	int ret=::epoll_create1(0);
	if(ret==-1){
		perror("epoll_create1");
	}
	//返回epollfd
	return ret;
}
#if 0
typedef union epoll_data {
	void *ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
} epoll_data_t;

struct epoll_event {
	uint32_t events;      /* Epoll events */
	epoll_data_t data;    /* User data variable */
};

#endif
//将一个描述符添加到epoll监控中
void EventLoop::addEpollFdRead(int fd)
{
	struct epoll_event evt;
	evt.data.fd=fd;
	evt.events=EPOLLIN;
	int ret=epoll_ctl(_efd,EPOLL_CTL_ADD,fd,&evt);
	if(-1==ret){
		perror("epoll_ctl");
	}
}

//将一个描述符从epoll监控中删除
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
