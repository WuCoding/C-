#include "head.h"
#include "work_que.h"
#include "factory.h"

//队列初始化
int queInit(pQue_t pQue,int capacity)
{
	memset(pQue,0,sizeof(Que_t));
	pQue->queHead=pQue->queTail=NULL;
	pQue->capacity=capacity;
	pQue->size=0;
	pthread_mutex_init(&pQue->mutex,NULL);
	return 0;
}

//将任务放入任务队列
int queInsert(pQue_t pQue,pNode_t pNewTask)//在插入时已经上锁所以只需要插入就ok
{
	//尾插法
	if(0==pQue->size)//队列为空
	{
		pQue->queHead=pQue->queTail=pNewTask;
	}else{//队列不为空
		pQue->queTail->pNext=pNewTask;
		pQue->queTail=pNewTask;
	}
	pQue->size++;
	return 0;
}

//将任务从任务队列中拿出来
int queGet(pQue_t pQue,pNode_t *ppNewTask)
{
	if(1==pQue->size)//队列中只有一个任务
	{
		*ppNewTask=pQue->queHead;
		pQue->queHead=pQue->queTail=NULL;
	}else{ //队列中有多个任务
		*ppNewTask=pQue->queHead;
		pQue->queHead=pQue->queHead->pNext;
	}
	pQue->size--;
	return 0;
}




