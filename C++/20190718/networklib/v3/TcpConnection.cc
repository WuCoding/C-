#include "TcpConnection.h"
#include "InetAddress.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>

namespace wd
{

//构造函数，只传fd描述符
TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdownWrite(false)
{}

//析构函数
TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite){//如果没有关闭该描述符的写操作
		shutdown();//执行关闭该描述符的写操作
	}
}

//从该描述符中读取一行
string TcpConnection::receive()
{
	char buff[65536]={0};
	_socketIO.readline(buff,sizeof(buff));
	return string(buff);
}

//向该描述符输入数据
void TcpConnection::send(const string &msg)
{
	_socketIO.writen(msg.c_str(),msg.size());
}

//关闭该描述符的写操作
void TcpConnection::shutdown()
{
	if(!_isShutdownWrite){//如果没有关闭该描述符的写操作
		_isShutdownWrite=true;
		_sock.shutdownWrite();
	}
}

//返回本地地址和对端地址的信息
string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss<< _localAddr.ip()<<":"<<_localAddr.port()<<"-->"
		<<_peerAddr.ip()<<":"<<_peerAddr.port();
	return oss.str();
}

//通过绑定的描述符来获得本地地址
InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	int ret=getsockname(_sock.fd(),(struct sockaddr*)&addr,&len);
	if(-1==ret){
		perror("getsockname");
	}
	return InetAddress(addr);
}

//通过绑定的描述符来获得对端地址
InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	int ret=getpeername(_sock.fd(),(struct sockaddr*)&addr,&len);
	if(-1==ret){
		perror("getpeername");
	}
	return InetAddress(addr);
}

//设置链接时的回调函数
void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb)
{
	_onConnection=std::move(cb);
}

//设置收到信息时的回调函数
void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
	_onMessage=std::move(cb);
}

//设置关闭套接字时的回调函数
void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
	_onClose=std::move(cb);
}

//执行链接时的回调函数
void TcpConnection::handleConnectionCallback()
{
	if(_onConnection){//如果回调函数不为空
		_onConnection(share_from_this());
	}
}

//执行收到信息时的回调函数
void TcpConnection::handleMessageCallback()
{
	if(_onMessage){//如果回调函数不为空
		_onMessage(shared_from_this());
	}
}

//关闭套接字时的回调函数
void TcpConnection::handleCloseCallback()
{
	if(_onClose){//如果回调函数不为空
		_onClose(share_from_this());
	}
}
}//end of namespace wd








































