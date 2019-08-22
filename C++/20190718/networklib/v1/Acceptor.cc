#include "Acceptor.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//传port端口号的构造函数
Acceptor::Acceptor(unsigned short port)
: _addr(port) 		//调用InetAddress类型的传port的构造函数，ip为本机ip
, _listensock() 	//调用Socket类型的无参构造函数，创建一个描述符
{}

//传ip地址和port端口号的构造函数
Acceptor::Acceptor(const string &ip,unsigned short port)
: _addr(ip,port)	//调用InetAddress类型的传ip和port的构造函数
, _listensock()		//调用Socket类型的无参构造函数，创建一个描述符
{}

//就绪函数
void Acceptor::ready()
{
	//重用地址
	setReuseAddr(true);
	//重用端口
	setReusePort(true);
	//套接口绑定一个端口号和IP地址
	bind();
	//处于监听状态
	listen();
}
#if 0

头文件：#include <sys/types.h>
	#include <sys/socket.h>

函数原型：
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

参数解释：
	>sockfd：
	标识一个套接口的描述字。
	>level：
	选项定义的层次；支持SOL_SOCKET、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6。
	>optname：
	需设置的选项。
	>optval：
	指针，指向存放选项待设置的新值的缓冲区。
	>optlen：
	optval缓冲区长度。
返回值：
	无错误返回0
#endif

//设置重用地址函数
void Acceptor::setReuseAddr(bool on)
{
	int one=on;
	if(setsockopt(_listensock.fd(),SOL_SOCKET,SO_REUSEADDR,&one,sizeof(one))<0){
		//打印错误信息
		perror("setsockopt");
	}
}

//设置重用端口号
void Acceptor::setReusePort(bool on)
{
	int one=on;
	if(setsockopt(_listensock.fd(),SOL_SOCKET,SO_REUSEPORT,&one,sizeof(one))<0){
		//打印错误信息
		perror("setsockopt");
	}
}

//将socket监听描述符绑定到特定ip和端口号port上
void Acceptor::bind()
{
#if 0
函数原型：
	>int bind(int sockfd,struct sockaddr* my_addr,int addrlen);
sockfd:
	>监控链接的套接口，用来绑定服务器端的ip和port
my_addr:
	>结构体指针变量
addrlen:
	>sockaddr的结构体长度，通常是计算sizeof(struct sockaddr)
返回值：
	>成功返回0，失败返回-1
#endif
	int ret=::bind(_listensock.fd(),(struct sockaddr *)_addr.getInetAddressPtr(),
			sizeof(struct sockaddr));
	if(-1==ret){
		perror("listen");
	}
}

//使描述符处于监听状态
void Acceptor::listen()
{
#if 0
函数原型：
	>int listen(int sockfd,int backlog)
sockfd:
	>为之前绑定ip和port的套接字
backlog:
	>指定同时能处理的最大的链接要求，通常为10或者5，最大可设至128
返回值：
	>成功返回0，失败返回-1
#endif
	int ret=::listen(_listensock.fd(),10);
	if(-1==ret){
		perror("listen");
	}
}

//接受链接请求函数
int Acceptor::accept()
{
#if 0
函数原型：
	>int accept(int s,struct sockaddr* addr,int* addrlen)
s:
	>为之前绑定ip和port的套接字
addr:
	>为结构体指针变量，系统会把远程主机的信息（远程主机的地址和端口号信息）
	>保存到这个指针所指的结构体中。
addrlen:
	>表示结构体的长度，为整型指针，&(sizeof(struct sockaddr))。
返回值：
	>成功则返回新的socket处理码new_fd，失败返回-1
#endif
	int peerfd=::accept(_listensock.fd(),NULL,NULL);
	if(-1==peerfd){
		perror("accept");
	}
	return peerfd;
}

}//end of namespace wd







































