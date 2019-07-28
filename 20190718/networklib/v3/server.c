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
#define ERR_EXIT(m)\
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
#define MAXEVENTS 2048
void do_service(int sockfd);

int main(int argc,const char *argv[])
{
	//创建一个监听链接的套接字
	int listenfd=socket(PF_INET,SOCK_STREAM,0);
	if(listen==-1){
		ERR_EXIT("socket");
	}

	//设置地址复用
	int on=1;
	int ret=setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret<0){
		ERR_EXIT("setsockopt");
	}
	
	//设置地址
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.175.128");
	addr.sin_port=htons(8111);
	
	//将套接字和地址绑定
	ret=bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret==-1){
		ERR_EXIT("bind");
	}

	//将套接字进入监听模式
	ret=listen(listenfd,SOMAXCONN);//第二个参数为建立半连接的最大数量
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
	
	//将监听链接的描述符加入到epoll监控队列中
	struct epoll_event evt_listen;
	evt_listen.data.fd=listenfd;
	evt_listen.events=EPOLLIN;//|EPOLLET(边缘触发)
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&evt_listen);
	if(-1==ret){
		perror("epoll_ctl_add error");
		exit(EXIT_FAILURE);
	}

	//创建存储就绪描述符epoll_event结构体的数组
	struct epoll_event *events=(struct epoll_event*)calloc(MAXEVENTS,sizeof(struct epoll_event));

	//std::vector<epoll_event> events;
	
	while(1)
	{
		int idx;
		//存储有多少个描述符已就绪
		int nready=epoll_wait(efd,events,MAXEVENTS,-1);
		for(idx=0;idx!=nready;++idx)
		{
			int fd=events[idx].data.fd;
			if(fd==listenfd){//有新的客户端链接到来
				if(events[idx].events & EPOLLIN){//监听的是该描述符的可读事件
					int peerfd=accept(fd,NULL,NULL);
					//TcpConnection
					if(-1==peerfd){
						perror("accept error");
						exit(EXIT_FAILURE);
					}
					//将该套接字加入到epoll监控队列中
					struct epoll_event ev;
					ev.data.fd=peerfd;
					ev.events=EPOLLIN;
					ret=epoll_ctl(efd,EPOLL_CTL_ADD,peerfd,&ev);
					if(-1==ret){
						perror("epoll_ctl_add error");
						exit(EXIT_FAILURE);
					}
				}
				//建立连接后，要进行的操作可以使用回调函数来做
				onConnection();
			}else{//有别的客户端的信息到来
				if(events[idx].events & EPOLLIN){
					//监听的是该描述符是否可读
					char recvbuf[1024]={0};
					int nread=read(fd,recvbuf,sizeof(recvbuf));
					if(0==nread){//表示该描述符可读是因为对端关闭
						//将该描述符从epoll监控队列中删除
						struct epoll_event ev;
						ev.data.fd=fd;
						ret=epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev);
						if(-1==ret){
							perror("epoll_ctl_del error");
							exit(EXIT_FAILURE);
						}
						//关闭该套接字
						close(fd);
						//执行关闭时的回调函数
						onClose();
						continue;
					}

					//走到这里说明是真的有信息
					//对信息进行处理通过回调函数
					onMessage();
				}
			}
		}//end for
	}
	//释放events的堆空间数组
	free(events);
	//关闭监听链接的描述符
	close(listenfd);
	//关闭epoll描述符
	close(efd);

	return 0;
}
#if 0
void do_service(int sockfd)
{
	char recvbuf[1024]={0};
	while(1)
	{
		int nread=read(sockfd,recvbuf,sizeof(recvbuf));
		if(nread==-1){//读取出错
			if(errno==EINTR){//中断导致的出错
				continue;
			}
			ERR_EXIT("read");
		}else if(nread==0){//对端关闭
			printf("close....\n");
			exit(EXIT_SUCCESS);
		}

		write(sockfd,recvbuf,strlen(recvbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
}
#endif





























