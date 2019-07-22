#ifndef __FACTORY_H__
#define __FACTORY_H__
#include "head.h"
#include "work_que.h"

typedef struct{
	Que_t que;//任务队列
	pthread_cond_t cond;//条件变量
	pthread_t *pthid;//子线程ID
	int threadNum;//子线程数目
	int startFlag;//开始工作标志
}Factory_t,*pFactory_t;

int factoryInit(pFactory_t,int,int);
int factoryStart(pFactory_t);
#endif
