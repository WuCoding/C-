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
	//创建一个用于链接的描述符
	int peerfd=socket(PF_INET,SOCK_STREAM,0);
	if(peerfd==-1){
		ERR_EXIT("socket");
	}

	//用来存储本地的地址（客户端）
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr("192.168.30.120");//localhost
	addr.sin_port=htons(8888);
	
	//将链接描述符和本地地址绑定
	socklen_t len=sizeof(addr);
	int ret=connect(peerfd,(struct sockaddr*)&addr,len);
	if(ret==-1){
		ERR_EXIT("Connect");
	}

	//从链接描述符中读取数据
	char buff[1024]={0};
	read(peerfd,buff,sizeof(buff));
	printf("%s\n",buff);

}

void do_service(int sockfd)
{
	char recvbuf[1024]={0};
	char sendbuf[1024]={0};
	while(1)
	{
		//将要发送的数据存入sendbuf中
		fgets(sendbuf,sizeof(sendbuf),stdin);
		//将要发送的数据写入套接字描述符中
		write(sockfd,sendbuf,strlen(sendbuf));

		//从套接字中读取数据
		int nread=read(sockfd,recvbuf,sizeof(recvbuf));
		if(nread==-1){//读取出错
			if(errno==EINTR){//中断导致的读取错误
				continue;
			}
			//走到这表示其他错误
			ERR_EXIT("read");
		}else if(nread==0){//对端关闭
			printf("server close\n");
			//关闭该套接字
			close(sockfd);
			exit(EXIT_SUCCESS);
		}

		//打印接收到的信息
		printf("receive msg:%s",recvbuf);

		memset(recvbuf,0,sizeof(recvbuf));
		memset(sendbuf,0,sizeof(sendbuf));
	}
}

