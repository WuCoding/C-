#pragma once

#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class TaskQueue;
//因为下面类型声明中只用到了TaskQueue类型的引用
//所以只需要一个前向声明即可，可在下面类型的实现
//文件中再包含TaskQueue类型的头文件


//生产者线程类型
class Producer
: public Thread
{
	public:
		//构造函数
		Producer(TaskQueue &que)
		: _que(que)
		{}

	private:
		//重载的子线程执行的函数
		void run();
	private:
		//数据成员
		TaskQueue & _que; //任务队列类型的对象的引用
};

}//end of namespace wd
