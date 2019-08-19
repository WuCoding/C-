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
	//使用回调函数
	using ThreadCallback=function<void()>;

	Thread(ThreadCallback &&cb)
	: _pthid(0)
	, _isRunning(false)
	, _cb(std::move(cb))
	{}

	void start();
	void join();

	~Thread();

private:
	//线程函数
	static void *threadfunc(void arg);
private:
	//数据成员
	pthread_t _pthid;//线程id
	bool _isRunning;
	ThreadCallback _cb;//回调函数
};

}//end of namespace wd

