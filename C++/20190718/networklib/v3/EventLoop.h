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

class Acceptor;//将一个地址和套接字绑定，并将该套接字处于监听链接模式
class TcpConnection;//传入一个fd描述符，获得本地和对端的地址

class EventLoop
{
	public:
		using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
		using TcpConnectionCallback=std::function<void(const TcpConnectionPtr&)>;

		//构造函数
		EventLoop(Acceptor &acceptor);//acceptor中有一个地址一个绑定的fd

		void loop();
		void unloop();
		//设置链接时的回调函数
		void setConnectionCallback(TcpConnectionCallback &&cb)
		{
			_onConnection=std::move(cb);
		}
		//设置收到信息时的回调函数
		void setMessageCallback(TcpConnectionCallback &&cb)
		{
			_onMessage=std::move(cb);
		}
		//设置关闭套接字时的回调函数
		void setCloseCallback(TcpConnectionCallback &&cb)
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
		//epoll描述符
		int _efd;
		Acceptor & _acceptor;
		vector<struct epoll_event> _eventList;
		map<int, TcpConnectionPtr> _conns;
		bool _isLooping;

		//回调函数
		TcpConnectionCallback _onConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
};
}//end of namespace wd
#endif
		
