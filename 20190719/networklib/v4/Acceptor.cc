#include "Acceptor.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//传递port构造函数
Acceptor::Acceptor(unsigned short port)
: _addr(port)//调用类InetAddress的传port构造函数，ip为本机ip
, _listensock()//调用类Socket的无参构造函数，创建一个套接字
{}

//传递ip和port构造函数
Acceptor::Acceptor(const string &ip,unsigned short port)
: _addr(ip,port)//调用类InetAddress的传ip和port构造函数
, _listensock()//调用类Socket的无参构造函数，创建一个套接字
{}

//将该等待链接一方进入等待链接就绪状态
void Acceptor::ready()
{
	//设置地址可重用
	setReuseAddr(true);
	//设置端口可重用
	setReusePort(true);
	//将套接字与本进程地址绑定
	bind();
	//将该套接字进入监听模式
	listen();
}

//设置地址可重用
void Acceptor::setReuseAddr(bool on)
{
	int one=on;
	int ret=setsockopt(_listensock.fd(),SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one));
	if(ret<0){
		perror("setsockopt");
	}
}

//设置端口可重用
void Acceptor::setReusePort(bool on)
{
	int one=on;
	int ret=setsockopt(_listensock.fd(),SOL_SOCKET,SO_REUSEPORT,&one,sizeof(one));
	if(ret<0){
		perror("setsockopt");
	}
}

//将套接字和地址绑定
void Acceptor::bind()
{
	int ret=::bind(_listensock.fd(),(struct sockaddr *)_addr.getInetAddressPtr(),
			sizeof(struct sockaddr));
	if(-1==ret){
		perror("listen");
	}
}

//将套接字进行监听
void Acceptor::listen()
{
	//第2个参数为最大半连接数，即只进行了connect，但还没有跟服务器进行accept
	//相当于你connect一个客户端，就往队列里加一个，accept一个客户端就从队列中
	//减一个，这个队列的最大长度就是该函数的第二个参数
	int ret=::listen(_listensock.fd(),10);
	if(-1==ret){
		perror("listen");
	}
}

//和客户端进行链接，返回进行数据传输的套接字
int Acceptor::accept()
{
	//获得进行数据传输的套接字，三次握手发生在connect和accept期间
	int peerfd=::accept(_listensock.fd(),NULL,NULL);
	if(-1==peerfd){
		perror("accept");
	}
	return peerfd;
}

}//end of namespace wd


