#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__

#include "MutexLock.h"

#include <sys/epoll.h>

#include <map>
#include <memory>
#include <vector>
#include <functional>
using std::vector;
using std::map;
using std::shared_ptr;

namespace wd
{

class Acceptor;
class TcpConnection;

class EventLoop
{
public:
	using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
	using TcpConnectionCallback=std::function<void(const TcpConnectionPtr&)>;
	using Functor=std::function<void()>;
	//构造函数
	EventLoop(Acceptor & acceptor);

	void loop();
	void unloop();
	void runInLoop(Functor && cb);

	//注册回调函数
	void setConnectionCallback(TcpConnectionCallback &&cb)
	{
		_onConnection=std::move(cb);
	}
	void setMessageCallback(TcpConnectionCallback &&cb)
	{
		_onMessage=std::move(cb);
	}
	void setCloseCallback(TcpConnectionCallback &&cb)
	{
		_onClose=std::move(cb);
	}

private:
	void waitEpollFd();
	void handleNewConnection();//有新的链接请求
	void handleMessage(int fd);//有新的消息到达
	void handleRead();
	void wakeup();
	int createEpollFd();//创建一个epoll描述符
	int createEventFd();//创建一个eventfd描述符
	void doPendingFunctors();

	void addEpollFdRead(int fd);//增加一个epoll监控的描述符的读操作
	void delEpollFdRead(int fd);//删除一个epoll监控的描述符的读操作
	bool isConnectionClosed(int fd);//判断链接是否关闭

private:
	int _efd;//epoll描述符
	int _eventfd;//事件描述符
	Acceptor &_acceptor;
	vector<struct epoll_event> _eventList;//唤醒事件队列
	map<int,TcpConnectionptr> _conns;
	bool _isLooping;

	MutexLock _mutex;
	vector<Functor> _pendingFunctors;

	TcpConnectionCallback _onConnection;
	TcpConnectionCallback _onMessage;
	TcpConnectionCallback _onClose;

};

}//end of namespace wd

#endif




