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
		//构造函数，传递任务队列的容量
		TaskQueue(size_t queSize=10);

		//判断是否为空
		bool empty() const;

		//判断是否已满
		bool full() const;
		
		//将任务放入任务队列
		void push(int number);

		//将任务从任务队列中拿出
		int pop();
	private:
		//数据成员
		size_t _queSize;//任务队列的容量
		queue<int> _que;//任务队列
		MutexLock _mutex;//互斥锁
		Condition _notFull;//条件变量，不满
		Condition _notEmpty;//条件变量，不空
};

}//end of namespace wd
