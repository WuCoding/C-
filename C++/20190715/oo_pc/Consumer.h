#pragma once

#include "Thread.h"

namespace wd
{

class TaskQueue;

//消费者线程类型
class Consumer
: public Thread
{
	public:
		//构造函数
		Consumer(TaskQueue & que)//传入任务队列的引用
		: _que(que)
		{}

	private:
		void run();

	private:
		//任务队列的引用
		TaskQueue & _que;
};

}//end of namespace wd
