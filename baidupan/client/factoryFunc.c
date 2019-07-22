#include "head.h"
#include "work_que.h"
#include "factory.h"

//初始化Factory_t结构体
int factoryInit(pFactory_t pFactory,char *ip,char *port,int threadNum,int capacity)
{
	memset(pFactory,0,sizeof(Factory_t));
	//初始化ip
	strcpy(pFactory->ip,ip);
	//初始化port
	strcpy(pFactory->port,port);
	//初始化que
	queInit(&pFactory->que,capacity);
	//初始化cond
	pthread_cond_init(&pFactory->cond,NULL);
	//初始化pthid
	pthread_t *pthid=(pthread_t*)calloc(threadNum,sizeof(pthread_t));
	pFactory->pthid=pthid;
	//初始化threadNum
	pFactory->threadNum=threadNum;
	//初始化startFlag
	pFactory->startFlag=0;

	return 0;
}


//子线程函数
void *threadFunc(void* pFactor)
{
	pFactory_t pFactory=(pFactory_t)pFactor;
	//从任务队列取任务
	pNode_t pNewTask;
	int socketFd,clientType;
	Train_t dataTrain;
	while(1)
	{
		pthread_mutex_lock(&pFactory->que.mutex);
		if(0==pFactory->que.size)//队列里无任务，进入睡眠状态
		{
			pthread_cond_wait(&pFactory->cond,&pFactory->que.mutex);
		}
		queGet(&pFactory->que,&pNewTask);
		pthread_mutex_unlock(&pFactory->que.mutex);
		if(0==strcmp(pNewTask->commendType,"gets"))//下载文件任务
		{
			clientType=1;
			//与服务期再次建立链接
			tcpConnect(&socketFd,pFactory->ip,pFactory->port);
			//向服务器发送我是谁
			memset(&dataTrain,0,sizeof(Train_t));
			dataTrain.dataLen=sizeof(int);
			memcpy(dataTrain.data,&clientType,dataTrain.dataLen);
			send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
			//发送给服务器子线程文件名
			memset(&dataTrain,0,sizeof(Train_t));
			dataTrain.dataLen=strlen(pNewTask->fileName);
			memcpy(dataTrain.data,pNewTask->fileName,dataTrain.dataLen);
			send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
			//接收文件
			recvFile(socketFd);
			printf("\r%s下载完成\ncommend:",pNewTask->fileName);
			fflush(stdout);
		}else if(0==strcmp(pNewTask->commendType,"puts"))//上传文件任务
		{
			clientType=2;
			//与服务器再次建立连接
			tcpConnect(&socketFd,pFactory->ip,pFactory->port);
			//向服务器发送我是谁
			memset(&dataTrain,0,sizeof(Train_t));
			dataTrain.dataLen=sizeof(int);
			memcpy(dataTrain.data,&clientType,dataTrain.dataLen);
			send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
			//发送目录id
			memset(&dataTrain,0,sizeof(Train_t));
			dataTrain.dataLen=strlen(pNewTask->id);
			memcpy(dataTrain.data,pNewTask->id,dataTrain.dataLen);
			send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
			//发送文件名
			memset(&dataTrain,0,sizeof(Train_t));
			dataTrain.dataLen=strlen(pNewTask->fileName);
			memcpy(dataTrain.data,pNewTask->fileName,dataTrain.dataLen);
			send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
			//发送文件
			sendFile(socketFd,pNewTask->fileName);
			printf("\r%s上传完成\ncommend:",pNewTask->fileName);
			fflush(stdout);
		}
	}
}

//启动线程池
int factoryStart(pFactory_t pFactory)
{
	if(0==pFactory->startFlag)//如果线程池未启动
	{
		int i;
		for(i=0;i<pFactory->threadNum;i++)//循环创建子线程
		{
			pthread_create(pFactory->pthid+i,NULL,threadFunc,pFactory);
		}
		pFactory->startFlag=1;
	}
	return 0;
}

