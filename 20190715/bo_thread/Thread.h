#pragma once

#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
using std::function;

namespace wd
{


//具体类
class Thread
: Noncopyable
{
	public:
		//function<void()>函数类型  对象为void()类型的对象
		using ThreadCallback=function<void()>;

		//构造函数
		Thread(ThreadCallback &&cb)
		: _pthid(0)
		, _isRunning(false)
		, _cb(std::move(cb))
		{}

		//开始函数
		void start();
		//回收函数
		void join();

		//析构函数
		~Thread();

	private:
		static void * threadfunc(void *arg);
	private:
		//数据成员
		pthread_t _pthid;//子线程id
		bool _isRunning;//是否创建该子线程的标志位
		ThreadCallback _cb;//void()类型的函数对象
};
}//end of namespace wd


