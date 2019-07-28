#include "TcpConnection.h"
#include "InetAddress.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>
#include <iostream>

using namespace std;
namespace wd
{

TcpConnection::TcpConnection(int fd)
: _sock(fd)
, _socketIO(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdownWrite(false)
{}

TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite){
		shutdown();
	}
	cout<<"~TcpConnection()"<<endl;
}

string TcpConnection::receive()
{
	char buff[65536]={0};
	_socketIO.readLine(buff,sizeof(buff));
	return string(buff);
}

void TcpConnection::send(const string &msg)
{
	_socketIO.writen(msg.c_str(),msg.size());
}

void TcpConnection::shutdown()
{
	if(!_isShutdownWrite){
		_isShutdownWrite=true;
		//套接字的停止写操作
		_sock.shutdownWrite();
	}
}

string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss<<_localAddr.ip()<<":"<<_localAddr.port()<<"-->"
		<<_peerAddr.ip()<<":"<<_peerAddr.port();
	return oss.str();
}

InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	if(getsockname(_sock.fd(),(struct sockaddr*)&addr,&len)==-1){
		perror("getsockname");
	}
	return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	if(getpeername(_sock.fd(),(struct sockaddr*)&addr,&len)==-1){
		perror("getpeername");
	}
	return InetAddress(addr);
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb)
{
	_onConnection=std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
	_onMessage=std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
	_onClose=std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnection){
		_onConnection(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessage){
		_onMessage(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(_onClose){
		_onClose(shared_from_this());
	}
}

}//end of namespace wd










































