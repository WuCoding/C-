#pragma once

#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{

class Thread
: Noncopyable
{
	public:
		//构造函数
		Thread()
		: _pthid(0)
		, _isRunning(false)
		{}

		//开始线程函数
		void start();

		//回收线程函数
		void join();

		//该类含有纯虚函数，所以析构函数也为虚函数
		virtual ~Thread();
	
	private:
		//纯虚函数
		virtual void run()=0;//待执行的任务
		//子线程要执行的线程函数，线程函数类型都为 void* func(void*)
		//所以要设为static成员函数，不然非static成员函数都会自动含有this指针，
		//参数个数不匹配
		static void * threadfunc(void * arg);
	private:
		//数据成员
		pthread_t _pthid;//线程id
		bool _isRunning;//标志位，标志线程是否开始运行
};
}//end of namespace wd
