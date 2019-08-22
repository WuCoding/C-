#pragma once

#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"

#include <queue>
using std::queue;

namespace wd
{

//ElemType来表示任务的指针
using ElemType=Task *;

class TaskQueue
{
public:
	//构造函数
	TaskQueue(size_t queSize=10);

private:
	//数据成员
	size_t _queSize;//任务队列长度
	queue<ElemType> _que;//任务队列
	MutexLock _mutex;//互斥锁
	Condition _notFull;//任务队列不满的条件变量
	Condition _notEmpty;//任务队列不空的条件变量
	bool _flag;
};

}//end of namespace wd

