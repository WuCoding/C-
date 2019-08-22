#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__

#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"

#include <string>
using std::string;

namespace wd
{
//以一个连接好了的一端的fd为一个TcpConnection类型的对象，通过这个fd来进行各种操作
//class类的默认继承方式为private
//struct结构体的默认继承方式为public
class TcpConnection
:Noncopyable
{
	public:
		//构造函数
		TcpConnection(int fd);
		//析构函数
		~TcpConnection();

		//接收操作函数
		string receive();
		//发送操作函数
		void send(const string &msg);

		string toString() const;
		void shutdown();
	private:
		InetAddress getLocalAddr(int fd);
		InetAddress getPeerAddr(int fd);
	private:
		//数据成员
		Socket _sock;//套接字
		SocketIO _socketIO;//从套接字中进行读写操作
		InetAddress _localAddr;//本地地址
		InetAddress _peerAddr;//对端地址
		bool _isShutdownWrite;
};

}//end of namespace wd

#endif
