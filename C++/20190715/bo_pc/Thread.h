#pragma once

#include "Noncopyable.h"

#include <pthread.h>

#include <functional>
using std::function;

namespace wd
{
//具体类
class Thread
: Noncopyable  //不写继承方式则为默认继承方式private
{
	public:
		using ThreadCallback=function<void()>;

		//移动构造函数
		Thread(ThreadCallback && cb)
		: _pthid(0)
		, _isRunning(false)
		, _cb(std::move(cb))
		{}

		//线程启动函数
		void start();
		//线程回收函数
		void join();

		//析构函数
		~Thread();

	private:
		//创建子线程时传入的线程执行函数，传入this指针
		static void * threadfunc(void * arg);

	private:
		//数据成员
		pthread_t _pthid;	//子线程的id
		bool _isRunning; 	//子线程是否启动标志
		ThreadCallback _cb;	//回调函数，子线程具体执行的操作
};

}//end of namespace wd
