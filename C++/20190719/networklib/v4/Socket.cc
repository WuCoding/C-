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
	//重新创建一个套接字
	_fd=socket(AF_INET,SOCK_STREAM,0);
	if(_fd==-1){
		perror("socket");
	}
}

//传描述符构造函数
Socket::Socket(int fd)
: _fd(fd)
{}

//获得描述符函数
int Socket::fd() const
{
	return _fd;
}

//关闭该描述符写操作
void Socket::shutdownWrite()
{
	::shutdown(_fd,SHUT_WR);
}

//析构函数
Socket::~Socket()
{
	::close(_fd);
}

}//end of namespace wd
