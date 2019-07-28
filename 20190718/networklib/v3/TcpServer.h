#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__

#include "Acceptor.h"
#include "EventLoop.h"
#include "TcpConnection.h"

namespace wd
{

using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
using TcpConnectionCallback=std::function<void(const TcpConnectionPtr&)>;

class TcpServer
{
	public:
		//构造函数，传入ip和port
		TcpServer(const string &ip,unsigned short port);
		void start();

		void setConnectionCallback(TcpConnectionCallback &&cb);
		void setMessageCallback(TcpConnectionCallback &&cb);
		void setCloseCallback(TcpConnectionCallback &&cb);

	private:
		//数据成员
		Acceptor _acceptor;//一个绑定了ip和port的监听链接描述符
		Socket _listensock;//监听描述符
};

}//end of namespace wd
#endif


