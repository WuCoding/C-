#include "Socket.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//无参构造函数
Socket::Socket()
{
	//创建一个ipv4 tcp描述符
	_fd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==_fd){
		perror("socket");
	}
}
//传描述符构造函数
Socket::Socket(int fd)
: _fd(fd)
{}

//获得该描述符
int Socket::fd() const
{
	return _fd;
}

//停止该描述符的写操作
void Socket::shutdownWrite()
{
	::shutdown(_fd,SHUT_WR);
}

//析构函数
Socket::~Socket()
{
	//关闭该描述符
	::close(_fd);
}

}//end of namespace wd


