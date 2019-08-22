#pragma once

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
using std::queue;

namespace wd
{

class TaskQueue
{
public:
	//构造函数
	TaskQueue(size_t queSize=10);

	//判断是否为空
	bool empty() const;
	//判断队列是否已满
	bool full() const;
	//将任务压入队列
	void push(int number);
	//将任务从队列中取出
	int pop();

private:
	//数据成员
	size_t _queSize;//任务队列长度
	queue<int> _que;//任务队列
	MutexLock _mutex;//互斥锁
	Condition _notFull;//不满的条件变量
	Condition _notEmpty;//不空的条件变量
};

}//end of namespace wd
