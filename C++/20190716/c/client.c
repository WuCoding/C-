#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m)\
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void do_service(int sockfd);

int main(int argc,const char *argv[])
{
	//用于和服务器连接的套接字
	int peerfd=socket(PF_INET,SOCK_STREAM,0);
	if(-1==peerfd){
		ERR_EXIT("socket");
	}

	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	//addr.sin_addr.s_addr=inet_addr("192.168.30.128");
	addr.sin_addr.s_addr=INADDR_ANY;//localhost 自动填入本机的ip地址
	addr.sin_port=htons(8888);
	
	//进行链接
	socklen_t len=sizeof(addr);
	int ret=connect(peerfd,(struct sockaddr*)&addr,len);
	if(-1==ret){
		ERR_EXIT("Connect");
	}

	//链接之后从套接字中读取信息
	char buf[1024];
	memset(buf,0,sizeof(buf));
	read(peerfd,buf,sizeof(buf));
	printf("%s\n",buf);

	//跟服务器端进行交流
	do_service(peerfd);

	return 0;
}




void do_service(int sockfd)
{
	char recvbuf[1024]={0};
	char sendbuf[1024]={0};

	while(1)
	{
		//从标准输入中获取要发送的信息
		fgets(sendbuf,sizeof(sendbuf),stdin);
		//将要发送的信息写入到套接字中
		write(sockfd,sendbuf,strlen(sendbuf));

		//从套接字中读取信息
		int nread=read(sockfd,recvbuf,sizeof(recvbuf));
		
		if(-1==nread){//读取信息失败
			if(errno==EINTR){//中断导致错误
				continue;
			}
			ERR_EXIT("read");
		}else if(0==nread){//对端关闭导致套接字可读
			printf("server close!\n");
			close(sockfd);
			exit(EXIT_SUCCESS);
		}

		//打印从套接字中获取到的信息
		printf("receive msg: %s\n",recvbuf);

		memset(recvbuf,0,sizeof(recvbuf));
		memset(sendbuf,0,sizeof(sendbuf));
	}
}
