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
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

#define MAXEVENTS 2048

//do_service()函数声明
void do_service(int sockfd);

int main(int argc,const char *argv[])
{
	//监听链接描述符创建
	int listenfd=socket(PF_INET,SOCK_STREAM,0);
	if(listen==-1){
		ERR_EXIT("socket");
	}

#if 0
头文件：
	#include <sys/types.h>
	#include <sys/socket.h>
函数原型：
	int setsockopt(int sockfd,int level,int optname,const void *optval,socklen_t optlen);
参数：
	sockfd:标识一个套接口的描述字
	level:选项定义的层次；支持SOL_SOCKET、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6
	optname:需设置的选项
	optval:指针，指向存放选项值的缓冲区
	optlen:optval缓冲区长度
#endif
	//设置地址复用
	int on=1;
	int ret=setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret<0){
		ERR_EXIT("setsockopt");
	}
#if 0
函数原型：
	int bind(int sockfd,struct sockaddr* my_addr,int addrlen);
参数：
	sockfd:用来绑定ip和port的监听链接的描述符
	my_addr:结构体指针变量
	addrlen:sockaddr的结构体长度。通常是计算sizeof(struct sockaddr);
返回值：
	成功返回0，失败返回-1

#endif

	//进行监听描述符和服务器地址的绑定
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;//ipv4
	addr.sin_addr.s_addr=inet_addr("192.168.149.128");
	addr.sin_port=htons(8111);
	ret=bind(listenfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret==-1){
		ERR_EXIT("bind");
	}
#if 0
函数原型：
	int listen(int sockfd,int backlog);
参数：
	sockfd:绑定完ip和port的监听套接字描述符
	backlog:指定同时能处理的最大链接要求，通常为10或者5。最大值可设为128
返回值：
	成功返回0，失败返回-1
#endif
	//进行监听
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

	//创建epoll_event结构体
	struct epoll_event evt_listen;
	//添加监听链接描述符
	evt_listen.data.fd=listenfd;
	evt_listen.events=EPOLLIN;//|EPOLLET(边缘触发)
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&evt_listen);
	if(-1==ret){
		perror("epoll_ctl add error");
		exit(EXIT_FAILURE);
	}

	struct epoll_event *events=(struct epoll_event*)calloc(
			MAXEVENTS,sizeof(struct epoll_event));
	//std::vector<epoll_event> events;
	
	while(1)
	{
		int idx;
		int nready=epoll_wait(efd,events,MAXEVENTS,-1);//-1表示永久等待
		for(idx=0;idx!=nready;++idx)
		{
			int fd=events[idx].data.fd;
			if(fd==listenfd){
				//新客户端链接到来
				if(events[idx].events & EPOLLIN){//按位与，二进位都为1结果才为1
					//表示该监控的描述符是监控它的可读
					//进行链接
					int peerfd=accept(fd,NULL,NULL);
					//TcpConnection
					if(-1==peerfd){
						perror("accept error");
						exit(EXIT_FAILURE);
					}
					//将新连接产生的套接字描述符加入到epoll监控中
					struct epoll_event ev;
					ev.data.fd=peerfd;
					ev.events=EPOLLIN;
					ret=epoll_ctl(efd,EPOLL_CTL_ADD,peerfd,&ev);
					if(-1==ret){
						perror("epoll_ctl_add error");
						exit(EXIT_FAILURE);
					}
				}
				//建立连接后执行一些操作，
				//这些操作交给回调函数来做
				onConnection();
			}else{//与客户端建立的fd
				if(events[idx].events & EPOLLIN){
					//监控的是该描述符的是否可读
					//用来存储描述符中的数据
					char recvbuf[1024]={0};
					//读入的字节数
					int nread=read(fd,recvbuf,sizeof(recvbuf));
					if(0==nread){
						//表示该描述符可读是因为对端关闭
						//将该描述符从epoll监控中删除
						struct epoll_event ev;
						ev.data.fd=fd;
						ret=epoll_ctl(efd,EPOLL_CTL_DEL,fd,&ev);
						if(-1==ret){
							perror("epoll_ctl_del error");
							exit(EXIT_FAILURE);
						}
						//将该描述符关闭
						close(fd);

						//执行一些关闭之后的操作
						//这些操作交给回调函数做
						onClose();
						continue;
					}

					//走到这里说明是真的有客户端发来信息
					//执行操作用回调函数来执行
					onMessage();
#if 0
					//打印出客户端发来的数据
					printf("recv msg:%s\n",recvbuf);
					//向该客户端发送数据
					int nwrite=write(fd,recvbuf,strlen(recvbuf));
					if(-1==nwrite){
						perror("send data error");
						close(fd);
					}
#endif
				}
			}
		}//end for
	}
	//释放在堆空间上的epoll_event数组
	free(events);
	//关闭监听链接的套接字
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
		if(nread==-1){
			if(errno==EINTR){
				//中断导致的错误
				continue;
			}
		}else if(nread==0){
			//对端关闭
			printf("close ...\n");
			exit(EXIT_SUCCESS);
		}

		//向该套接字写入数据
		write(sockfd,recvbuf,strlen(recvbuf));
		memset(recvbuf,0,sizeof(recvbuf));
	}
}
#endif



	


