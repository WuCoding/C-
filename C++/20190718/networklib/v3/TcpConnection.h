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
: Noncopyable //默认继承方式为private
, public std::enable_shared_from_this<TcpConnection>
{
	public:
		//构造函数，只传递一个描述符
		TcpConnection(int fd);
		//析构函数
		~TcpConnection();

		string receive();
		void send(const string &msg);

		string toString() const;
		void shutdown();

		//设置回调函数
		//设置链接时的回调函数
		void setConnectionCallback(const TcpConnectionCallback &cb);
		//设置收到信息时的回调函数
		void setMessageCallback(const TcpConnectionCallback &cb);
		//设置关闭套接字时的回调函数
		void setCloseCallback(const TcpConnectionCallback &cb);

		//执行回调函数
		//执行链接时的回调函数
		void handleConnectionCallback();
		//执行收到信息时的回调函数
		void handleMessageCallback();
		//执行关闭套接字的回调函数
		void handleCloseCallback();

	private:
		//获得fd描述符绑定的本地地址
		InetAddress getLocalAddr(int fd);
		//获得fd描述符绑定的对端地址
		InetAddress getPeerAddr(int fd);
	private:
		//套接字
		Socket _sock;
		//对套接字进行IO操作
		SocketIO _socketIO;
		//本地地址
		InetAddress _localAddr;
		//对端地址
		InetAddress _peerAddr;
		//是否已经将该描述符关闭写操作
		bool _isShutdownWrite;

		//链接时的回调函数
		TcpConnectionCallback _onConnection;
		//收到信息时的回调函数
		TcpConnectionCallback _onMessage;
		//关闭套接字时的回调函数
		TcpConnectionCallback _onClose;
};

}//end of namespace wd
#endif

