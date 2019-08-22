#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"

#include <string>
#include <memory>
#include <functional>
using std::string;
using std::function;

namespace wd
{

class TcpConnection;
using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
using TcpConnectionCallback=function<void(const TcpConnectionPtr&)>;

class TcpConnection
: Noncopyable  //默认private方式继承
, public std::enable_shared_from_this<TcpConnection>
{
	public:
		TcpConnection(int fd);
		~TcpConnection();

		string receive();
		void send(const string &msg);

		string toString() const;
		void shutdown();

		void setConnectionCallback(const TcpConnectionCallback &cb);
		void setMessageCallback(const TcpConnectionCallback &cb);
		void setCloseCallback(const TcpConnectionCallback &cb);

		void handleConnectionCallback();
		void handleMessageCallback();
		void handleCloseCallback();

	private:
		InetAddress getLocalAddr(int fd);
		InetAddress getPeerAddr(int fd);
	private:
		Socket _sock;
		SocketIO _socketIO;
		InetAddress _localAddr;
		InetAddress _peerAddr;
		bool _isShutdownWrite;

		TcpConnectionCallback _onConnection;
		TcpConnectionCallback _onMessage;
		TcpConnectionCallback _onClose;
};

}//end of namespace wd

#endif
