#include "Socket.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//无参构造函数，自己生成一个套接口描述符
Socket::Socket()
{
	//自己生成一个套接口描述符
	//第1个参数：AF_INET:IPv4网络协议，AF_INET6:IPv6网络协议
	//第2个参数：tcp: SOCK_STREAM，udp: SOCK_DGRAM
	//第3个参数：指定socket所使用的传输协议编号，通常为0
	//返回值：成功则返回套接口描述符，失败返回-1
	_fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==_fd){
		perror("socket");
	}
}

//传递fd描述符的构造函数
Socket::Socket(int fd)
: _fd(fd)
{}

//获得描述符函数
int Socket::fd()
{
	return _fd;
}

#if 0

头文件：	#include<sys/socket.h>
函数原型：	int shutdown(int sockfd,int how);
linux下成功则返回0，错误返回-1，错误码errno：
	>EBADF表示sockfd不是一个有效描述符；
	>ENOTCONN表示sockfd未连接；
	>ENOTSOCK表示sockfd是一个描述符而不是socket描述符。
how的方式有三种分别是
	>SHUT_RD（0）：关闭sockfd上的读功能，此选项将不允许sockfd进行读操作。
	>SHUT_WR（1）：关闭sockfd的写功能，此选项将不允许sockfd进行写操作。
	>SHUT_RDWR（2）：关闭sockfd的读写功能
#endif
//socket描述符关闭写功能函数
void Socket::shutdownWrite()
{
	//关闭该描述符的写功能
	::shutdown(_fd,SHUT_WR)
}

//析构函数，关闭该描述符
Socket::~Socket()
{
	::close(_fd);
}

}//end of namespace wd


