#include "head.h"
#include "work_que.h"
#include "factory.h"
int epollAdd(int eplFd,int fd)
{
	int ret;
	struct epoll_event event;
	event.events=EPOLLIN;
	event.data.fd=fd;
	ret=epoll_ctl(eplFd,EPOLL_CTL_ADD,fd,&event);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	return 0;
}

int epollDel(int eplFd,int fd)
{
	int ret;
	struct epoll_event event;
	event.events=EPOLLIN;
	event.data.fd=fd;
	ret=epoll_ctl(eplFd,EPOLL_CTL_DEL,fd,&event);
	ERROR_CHECK(ret,-1,"epoll_ctl");
	return 0;
}
