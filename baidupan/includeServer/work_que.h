#ifndef __WORK_QUE_H__
#define __WORK_QUE_H__
#include "head.h"
//服务器任务队列所用节点结构
typedef struct tag_node{
	int newFd;//建立链接的客户端描述符
	int flag;//进行的功能1.传输文件2.接收文件
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

