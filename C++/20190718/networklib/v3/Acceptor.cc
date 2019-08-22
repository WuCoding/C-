#include "Acceptor.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//传port的构造函数
Acceptor::Acceptor(unsigned short port)
: _addr(port) //调用InetAddress类型的传port的构造函数，ip为本机ip
, _listensock()  //调用Socket类型的无参构造函数
{}

//传ip和port的构造函数
Acceptor::Acceptor(const string &ip,unsigned short port)
: _addr(ip,port)//调用InetAddress类型的传ip和port的构造函数
, _listensock() //调用Socket类型的无参构造函数，自己创建一个描述符用来监听链接
{}

//准备函数
void Acceptor::ready()
{
	//设置地址可重用
	setReuseAddr(true);
	//设置port可重用
	setReusePort(true);
	//描述符与ip和port绑定
	bind();
	//将描述符进行监听
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

//设置port可重用
void Acceptor::setReusePort(bool on)
{
	int one=on;
	int ret=setsockopt(_listensock.fd(),SOL_SOCKET,SO_REUSEPORT,&one,sizeof(one));
	if(ret<0){
		perror("setsockopt");
	}
}

//将描述符与ip和port进行绑定
void Acceptor::bind()
{

















