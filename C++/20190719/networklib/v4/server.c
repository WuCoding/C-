#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
	do{ \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
#define MAXEVENTS 2048

void do_service(int sockfd);

int main(int argc,const char *argv[])
{
	//创建用于监听的描述符
	int listenfd=socket(PF_INET,SOCK_STREAM,0);
	if(listenfd==-1){
		ERR_EXIT("socket");
	}

	//设置地址复用
	int on=1;
	int ret=setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret<0){
		ERR_EXIT("setsockopt");
	}

	//进行地址绑定
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.175.128");
	addr.sin_port=htons(8111);
	ret=bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret==-1){
		ERR_EXIT("bind");
	}

	//进行监听操作
	ret=listen(listenfd,SOMAXCONN);
	if(ret==-1){
		ERR_EXIT("listen");
	}

	//创建epoll事件循环
	//int efd=epoll_create(MAXEVENTS);
	int efd=epoll_create1(0);//推荐使用这种方式
	if(-1==efd){
		perror("epoll_create error");
		exit(EXIT_FAILURE);
	}

	//将监听描述符加入到epoll监控队列中
	struct epoll_event evt_listen;
	evt_listen.data.fd=listenfd;
	evt_listen.events=EPOLLIN;//|EPOLLET(边缘触发);
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&evt_listen);
	if(-1==ret){
		perror("epoll_ctl add error");
		exit(EXIT_FAILURE);
	}

	//创建就绪描述符数组
	struct epoll_event *events=
		(struct epoll_event*)calloc(MAXEVENTS,sizeof(struct epoll_event));
	//std::vector<epoll_event> events;
	
	while(1)
	{
		int idx;
		int nready=epoll_wait(efd,events,MAXEVENTS,-1);
		for(idx=0;idx!=nready;++idx){
			int fd=events[idx].data.fd;
			if(fd==listenfd){//有新的客户端链接到来
				if(events[idx].events & EPOLLIN){//监控的是该事件的可读操作
					//获得链接的套接字
					int peerfd=accept(fd,NULL,NULL);
					if(-1==peerfd){
						perror("accept error");
						exit(EXIT_FAILURE);
					}

					//将新的套接字加入到epoll监控队列中
					struct epoll_event ev;
					ev.data.fd=peerfd;
					ev.events=EPOLLIN;
					ret=epoll_ctl(efd,EPOLL_CTL_ADD,peerfd,&ev);
					if(-1==ret){
						perror("epoll_ctl_add error");
						exit(EXIT_FAILURE);
					}
				}
				//建立新连接之后，要执行一些操作
				//使用回调函数来做
				onConnection();
			}else{//已经与客户端建立了链接的fd，有新的信息到来
				if(events[idx].events & EPOLLIN){
					//监控的是该描述符的可读操作
					char recvbuf[1024]={0};
					int nread=read(fd,recvbuf,sizeof(recvbuf));
					if(0==nread){//表示链接断开
						//将该描述符从epoll监控队列中删除
						struct epoll_event ev;
						ev.data.fd=fd;
						ret=epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev);
						if(-1==ret){
							perror("epoll_ctl_del error");
							exit(EXIT_FAILURE);
						}
						//关闭该描述符
						close(fd);
						//执行关闭时的回调函数
						onClose();
						continue;
					}
					//走到这里说明有新的信息
					//对客户端的数据进行处理
					onMessage();
				}
			}
		}//end for
	}
	//释放就绪描述符数组的堆空间
	free(events);
	//关闭epoll描述符
	close(efd);
	//关闭监听链接描述符
	close(listenfd);
	return 0;
}


