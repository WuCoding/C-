#include "head.h"
#include "work_que.h"
#include "factory.h"
//接收文件
int recvFile(int recvFd)
{
	//接收文件名
	char fileName[128]={0};
	int recvLen;
	recvCycle(recvFd,4,&recvLen);
	recvCycle(recvFd,recvLen,fileName);
	//创建该文件名的文件
	int fileFd;
	fileFd=open(fileName,O_RDWR|O_CREAT,0666);
	//接收文件大小
	long fileSize;
	recvCycle(recvFd,4,&recvLen);
	recvCycle(recvFd,recvLen,&fileSize);
	//接收文件内容
	char buf[1000]={0};
	while(1)
	{
		recvCycle(recvFd,4,&recvLen);
		if(0==recvLen)//文件接收结束
		{
			break;
		}
		recvCycle(recvFd,recvLen,buf);
		write(fileFd,buf,recvLen);
	}
	close(fileFd);
	return 0;
}
	
//发送文件
int sendFile(int sendFd,char *fileName)
{
	Train_t dataTrain;
	int fileFd;
	fileFd=open(fileName,O_RDONLY|O_CREAT);
	ERROR_CHECK(fileFd,-1,"open");
	//发送文件名
	dataTrain.dataLen=strlen(fileName);
	strcpy(dataTrain.data,fileName);//???用strcpy还是用别的
	send(sendFd,&dataTrain,4+dataTrain.dataLen,0);
	//发送文件大小
	struct stat buf;
	fstat(fileFd,&buf);
	dataTrain.dataLen=sizeof(buf.st_size);
	memcpy(dataTrain.data,&buf.st_size,dataTrain.dataLen);
	send(sendFd,&dataTrain,4+dataTrain.dataLen,0);
	//发送文件内容
	while((dataTrain.dataLen=read(fileFd,dataTrain.data,1000)))
	{
		send(sendFd,&dataTrain,4+dataTrain.dataLen,0);
	}
	//发送文件结束标识符
	send(sendFd,&dataTrain,4+dataTrain.dataLen,0);
	close(fileFd);
	return 0;
}

