#include "head.h"
#include "work_que.h"
#include "factory.h"

int tcpInit(int* pSocketFd,char* ip,char* port)
{
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	ERROR_CHECK(socketFd,-1,"socket");
	int ret;
	int reUse=1;
	ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reUse,sizeof(int));
	ERROR_CHECK(ret,-1,"setsockopt");
	struct sockaddr_in serAddr;
	bzero(&serAddr,sizeof(serAddr));
	serAddr.sin_family=AF_INET;
	serAddr.sin_port=htons(atoi(port));
	serAddr.sin_addr.s_addr=inet_addr(ip);
	ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
	ERROR_CHECK(ret,-1,"bind");
	listen(socketFd,10);
	*pSocketFd=socketFd;
	return 0;
}
	
