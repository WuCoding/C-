#include "TcpConnection.h"
#include "InetAddress.h"
#include "EventLoop.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>

namespace wd
{

//构造函数，fd为已经可以进行两端通信的全双工管道
TcpConnection::TcpConnection(int fd, EventLoop *loop)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdownWrite(false)
, _loop(loop)
{}

//析构函数
TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite){//如果停止写操作的标志位为false
		//执行shutdown()函数
		shutdown();
	}
}

//获得一行数据
string TcpConnection::receive()
{
	char buff[65536]={0};
	_socketIO.readline(buff,sizeof(buff));
	return string(buff);
}

//发送信息
void TcpConnection::send(const string &msg)
{
	_socketIO.writen(msg.c_str(),msg.size());
}

//向eventfd描述符可读时执行的函数容器中加入函数
void TcpConnection::sendInLoop(const string &msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::send,this,msg));
}

//停止执行向描述符中写入的操作
void TcpConnection::shutdown()
{
	if(!_isShutdownWrite){//如果停止写入操作为false
		_isShutdownWrite=true;
		//执行Socket对象的shutdownWrite()函数
		_sock.shutdownWrite();//停止该描述符的写操作
	}
}

//输出本端ip和port与对端ip和port
string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss<< _localAddr.ip()<<":"<<_localAddr.port()<<"-->"
		<<_peerAddr.ip()<<":"<<_peerAddr.port();
	return oss.str();
}

//获得本端地址
InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	int ret=getsockname(fd,(struct sockaddr*)&addr,&len);
	if(ret==-1){
		perror("getsockname");
	}
	return InetAddress(addr);
}

//获得对端的地址
InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	int ret=getpeername(fd,(struct sockaddr*)&addr,&len);
	if(ret==-1){
		perror("getpeername");
	}
	return InetAddress(addr);
}

//注册链接时的回调函数
void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb)
{
	_onConnection=std::move(cb);
}

//注册有新信息时的回调函数
void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
	_onMessage=std::move(cb);
}

//注册关闭链接时的回调函数
void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
	_onClose=std::move(cb);
}

//执行建立链接时的回调函数
void TcpConnection::handleConnectionCallback()
{
	if(_onConnection){
		_onConnection(shared_from_this());
	}
}

//执行有新信息时的回调函数
void TcpConnection::handleMessageCallback()
{
	if(_onMessage){
		_onMessage(shared_from_this());
	}
}

//执行关闭链接时的回调函数
void TcpConnection::handleCloseCallback()
{
	if(_onClose){
		_onClose(shared_from_this());
	}
}

}//end of namespace wd



