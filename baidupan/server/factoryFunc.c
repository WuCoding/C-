#include "head.h"
#include "work_que.h"
#include "factory.h"

//初始化Factory_t结构体
int factoryInit(pFactory_t pFactory,int threadNum,int capacity)
{
	memset(pFactory,0,sizeof(Factory_t));
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
	char fileName[20]={0};
	int dataLen;
	char id[20]={0};
	while(1)
	{
		pthread_mutex_lock(&pFactory->que.mutex);
		if(0==pFactory->que.size)//队列里无任务，进入睡眠状态
		{
			pthread_cond_wait(&pFactory->cond,&pFactory->que.mutex);
		}
		queGet(&pFactory->que,&pNewTask);
		pthread_mutex_unlock(&pFactory->que.mutex);
		if(1==pNewTask->flag)//发送文件任务
		{	
			//接收文件名
			recvCycle(pNewTask->newFd,4,&dataLen);
			recvCycle(pNewTask->newFd,dataLen,fileName);
			sendFile(pNewTask->newFd,fileName);
		}else if(2==pNewTask->flag)//接收文件内容
		{
			//接收目录id
			recvCycle(pNewTask->newFd,4,&dataLen);
			recvCycle(pNewTask->newFd,dataLen,id);
			//接收文件名
			recvCycle(pNewTask->newFd,4,&dataLen);
			recvCycle(pNewTask->newFd,dataLen,fileName);

			//将新信息插入到数据库中
			makeDirent("wcy",id,fileName,"f");
		
			//接收文件
			recvFile(pNewTask->newFd);
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

