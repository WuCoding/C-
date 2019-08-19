#pragma once 

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>
using std::queue;

namespace wd
{

using Task=std::function<void()>;
using ElemType=Task;

class TaskQueue
{
public:
	//构造函数，默认构造长度为10的任务队列
	TaskQueue(size_t queSize=10);

	bool empty() const;
	bool full() const;
	void push(ElemType &elem);
	ElemType pop();

	void wakeup();

private:
	//数据成员
	size_t _queSize;//任务队列的长度
	queue<ElemType> _que;//任务队列，用queue容器来承装Task对象
	MutexLock _mutex;//互斥锁
	Condition _notFull;//不满条件变量
	Condition _notEmpty;//不空条件变量
	bool _flag;
};

}//end of namespace wd
