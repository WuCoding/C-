#include "head.h"
#include "work_que.h"
#include "factory.h"

int recvCycle(int socketFd,int dataLen,void *buf)
{
	int ret,total = 0;
	while(total<dataLen)
	{
		ret=recv(socketFd,buf+total,dataLen-total,0);
		total+=ret;
	}
	return 0;
}



