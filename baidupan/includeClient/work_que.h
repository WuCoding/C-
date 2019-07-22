#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"
typedef struct tag_node{
	char commendType[20];//进行的功能gets下载文件puts上传文件
	char fileName[20];//进行操作的文件名
	char id[50];//当前目录id 在该目录下上传文件
	struct tag_node *pNext;
}Node_t,*pNode_t;
typedef struct{
	pNode_t queHead,queTail;//任务队列头和任务队列尾
	int capacity;//任务队列荷载能力
	int size;//任务队列当前任务数
	pthread_mutex_t mutex;//任务队列锁
}Que_t,*pQue_t;
int queInit(pQue_t,int);
int queInsert(pQue_t,pNode_t);
int queGet(pQue_t,pNode_t*);
#endif

