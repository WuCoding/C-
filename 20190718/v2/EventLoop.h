#ifndef __WD_EVENTLOOP_H__
#define __WD_EVENTLOOP_H__

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
		//构造函数，只传入一个Acceptor类型引用，该类型中将一个服务器
		//进入监听模式
		EventLoop(Acceptor &acceptor);
		void loop();
		void unloop();
		void setConnectionCallback(TcpConnectionCallback && cb)
		{
			_onConnection=std::move(cb);
		}
		void setMessageCallback(TcpConnectionCallback && cb)
		{
			_onMessage=std::move(cb);
		}
		void setCloseCallback(TcpConnectionCallback && cb)
		{
			_onClose=std::move(cb);
		}

	private:
		void waitEpollFd();
		void handleNewConnection();
		void handleMessage(int fd);
		int createEpollFd();

		void addEpollFdRead(int fd);
		void delEpollFdRead(int fd);
		bool isConnectionClosed(int fd);

	private:
		//数据成员
		int _efd;
		Acceptor & _acceptor;
		vector<struct epoll_event> _eventList;
		map<int,TcpConnectionPtr> _conns;
		bool _isLooping;

		TcpConnectionCallback _onConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
}
