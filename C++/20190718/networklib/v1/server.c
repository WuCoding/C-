#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
	//创建一个ipv4/tcp套接字
	int listenfd=socket(AF_INET,SOCK_STREAM,0);//默认情况下是阻塞的
	if(-1==listenfd){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	//设置地址可以复用
	//一个服务器程序主动关闭之后，立马可以重启
	int on=1;
	int ret=setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret<0){
		perror("setsockopt error");
		close(listenfd);
		exit(EXIT_FAILURE);
	}

#if 1
	//设置端口port可重用
	//实现系统级别的负载均衡，一个服务器程序可以在同一台物理主机的同一时刻启动多次
	ret=setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&on,sizeof(on));
	if(ret<0){
		perror("setsockopt error");
		close(listenfd);
		exit(EXIT_FAILURE);
	}
#endif

	//设置地址
	struct sockaddr_in serverAddr;
	printf("sizeof(struct sockaddr_in)=%ld\n",sizeof(struct sockaddr_in));
	memset(&serverAddr,0,sizeof(struct sockaddr_in));
	serverAddr.sin_family=AF_INET;//ipv4
	serverAddr.sin_port=htons(8888);
	serverAddr.sin_addr.s_addr=INADDR_ANY;
	//将my_addr.sin_port置为0，函数会自动为其选择一个未占用的端口来使用。
	//同样，通过将my_addr.sin_addr.s_addr置为INADDR_ANY，系统会自动填入
	//本机IP地址。
	
	//套接口绑定ip和port
	ret=bind(listenfd,(struct sockaddr*)&serverAddr,sizeof(struct sockaddr));
	if(-1==ret){
		perror("bind");
		close(listenfd);
		exit(EXIT_FAILURE);
	}
	
	//进入监听模式
	ret=listen(listenfd,10);//第二个参数的作用是，处理办理半连接状态的客户端的最大数量
	if(-1==ret){
		perror("listen");
		close(listenfd);
		exit(EXIT_FAILURE);
	}


	while(1)
	{
		//进行和客户端的链接
		//accept返回的的文件描述符，默认情况下也是阻塞的
		int peerFd=accept(listenfd,NULL,NULL);//由accept与客户端的connect完成三次握手

		char buff[1024]="welcome to server.";//用户态的应用缓冲区
		ret=write(peerFd,buff,strlen(buff));//将应用缓冲区的数据直接copy到内核（发送缓冲区）

		memset(buff,0,1024);
		printf(">pls client data:\n");
		ret=read(peerFd,buff,1024);//将内核接受缓冲区中的数据直接copy到应用缓冲区
		printf("%s\n",buff);
	}

	//关闭监听描述符
	close(listenfd);
	return 0;
}


























	



































