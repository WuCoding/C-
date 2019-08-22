#pragma once

#include "Noncopyable.h"

#include <pthread.h>

#include <functional>
using std::function;

namespace wd
{

//具体类
class Thread
: Noncopyable //默认为private继承方式
{
	public:
		//void()类型的回调函数
		using ThreadCallback=function<void()>;

		//构造函数
		Thread(ThreadCallback && cb)
		: _pthid(0)
		, _isRunning(false)
		, _cb(std::move(cb))
		{}

		void start();
		//回收线程函数
		void join();

		~Thread();
	private:
		//静态成员函数，因为线程函数类型为void*(void*)，只有一个参数
		//非静态成员函数，第一个参数会自动传入this指针，不符合线程函数
		//的类型，而静态成员函数，不含有this指针
		static void *threadfunc(void *arg);
	private:
		//数据成员
		pthread_t _pthid; //线程id
		bool _isRunning;//
		ThreadCallback _cb;//回调函数，类型为void()
};
}//end of namespace wd
