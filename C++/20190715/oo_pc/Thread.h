#pragma once

#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{

class Thread
:Noncopyable
{
	public:
		//构造函数
		Thread()
		: _pthid(0)
		, _isRunning(false)
		{}

		void start();
		void join();

		//析构函数，因为类中有虚函数，所以析构函数也设为虚函数
		virtual ~Thread();
	private:
		//纯虚函数
		virtual void run()=0;//待执行的任务，最终子线程要调用执行的操作
		static void * threadfunc(void *arg);//子线程进行操作的线程函数
	private:
		//数据成员
		pthread_t _pthid;
		bool _isRunning;
};

}//end of namespace wd
