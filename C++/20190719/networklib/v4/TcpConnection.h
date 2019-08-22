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

//前向声明
class TcpConnection;
using TcpConnectionPtr=std::shared_ptr<TcpConnection>;
using TcpConnectionCallback=function<void(const TcpConnectionPtr&)>;

class EventLoop;

class TcpConnection
: Noncopyable //默认采用private方式继承
, public std::enable_shared_from_this<TcpConnection>
{
public:
	//构造函数
	TcpConnection(int fd,EventLoop *);
	//析构函数
	~TcpConnection();

	string receive();
	void send(const string &msg);
	void sendInLoop(const string &msg);

	string toString() const;
	void shutDown();

	//注册回调函数
	void setConnectionCallback(const TcpConnectionCallback &cb);
	void setMessageCallback(const TcpConnectionCallback &cb);
	void setCloseCallback(const TcpConnectionCallback &cb);

	//回调函数执行函数
	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

private:
	//获得套接字绑定的本端地址
	InetAddress getLocalAddr(int fd);
	//获得套接字绑定的对端地址
	InetAddress getPeerAddr(int fd);

private:
	//数据成员
	Socket _sock;//套接字
	SocketIO _socketIO;//对套接字的IO操作
	InetAddress _localAddr;//本端地址
	InetAddress _peerAddr;//对端地址
	bool isShutdownWrite;//写操作是否关闭的标志位
	EventLoop * _loop;//EventLoop对象指针

	//链接时执行的回调函数
	TcpConnectionCallback _onConnection;
	TcpConnectionCallback _onMessage;
	TcpConnectionCallback _onClose;
	
};

}//end of namespace wd

#endif



