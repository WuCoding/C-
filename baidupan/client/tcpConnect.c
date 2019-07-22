#include "head.h"
#include "work_que.h"
#include "factory.h"

int tcpConnect(int *sockFd,char *ip,char *port)
{
	int socketFd;
	socketFd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serAddr;
	memset(&serAddr,0,sizeof(struct sockaddr_in));
	serAddr.sin_family=AF_INET;
	serAddr.sin_port=htons(atoi(port));
	serAddr.sin_addr.s_addr=inet_addr(ip);
	connect(socketFd,(struct sockaddr*)&serAddr,sizeof(struct sockaddr));
	*sockFd=socketFd;
	return 0;
}
