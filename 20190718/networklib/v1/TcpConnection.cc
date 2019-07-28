#include "TcpConnection.h"
#include "InetAddress.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>

namespace wd
{

//构造函数实现，对象成员都是以对象的形式存在。构造函数中将这些对象构造完毕
TcpConnection::TcpConnection(int fd)
: _sock(fd) //调用Socket类型的传值构造函数
, _socketIO(fd)//调用SocketIO类型的传值构造函数
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))//peer-to-peer对等网络，p2p
, _isShutdownWrite(false)
{}
//析构函数
TcpConnection::~TcpConnection()
{
	if(!_isShutdownWrite){//_isShutdownWrite为false，也就是没有被指定为停止书写
		shutdown();
	}
}

//从这个接收数据
string TcpConnection::receive()
{
	char buff[65536]={0};
	_socketIO.readline(buff,sizeof(buff));
	return string(buff);
}

//发送数据
void TcpConnection::send(const string &msg)
{
	//SocketIO类中的数据成员只有一个fd
	_socketIO.writen(msg.c_str(),msg.size());
}

//
void TcpConnection::shutdown()
{
	if(!_isShutdownWrite){//如果_isShutdownWrite为false
		_isShutdownWrite=true;
		//调用Socket类型的shutdownWrite函数
		_sock.shutdownWrite();
	}
}

//获得本地ip、port和对端ip、port
string TcpConnection::toString() const
{
	//ip()返回string类型，port()返回unsigned short类型
	std::ostringstream oss;
	oss<<_localAddr.ip()<<":"<<_localAddr.port()<<"-->"
		<<_peerAddr.ip()<<":"<<_peerAddr.port();
	//返回字符串流的字符串形式
	return oss.str();
}

#if 0
getsockname函数用于获取与某个套接字关联的本地协议地址 
getpeername函数用于获取与某个套接字关联的外地协议地址
定义如下：
#include<sys/socket.h>
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
#endif

//获得本地地址
InetAddress TcpConnection::getLocalAddr(int fd)
{
	//定义一个sockaddr_in结构体，作为传出参数
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	//getsockname()获得一个套接口的本地名字
	if(getsockname(_sock.fd(),(struct sockaddr*)&addr,&len)==-1){
		perror("getsockname");
	}
	return InetAddress(addr);
}

//获得对端地址
InetAddress TcpConnection::getPeerAddr(int fd)
{
	//作为传出参数
	struct sockaddr_in addr;
	socklen_t len=sizeof(struct sockaddr);
	if(getpeername(_sock.fd(),(struct sockaddr*)&addr,&len)==-1){
		perror("getpeername");
	}
	return InetAddress(addr);
}
}//end of namespace wd
























