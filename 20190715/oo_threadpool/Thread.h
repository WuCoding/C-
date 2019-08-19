#pragma once

#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{

class Thread
: Noncopyable
{
public:
	Thread()
	: _pthid(0)
	, _isRunning(false)
	{}

	//启动线程
	void start();
	//回收线程
	void join();

	//析构函数
	virtual ~Thread();
private:
	virtual void run()=0;//待执行的任务
	static void * threadfunc(void *arg);
private:
	pthread_t _pthid;
	bool _isRunning;
};

}//end of namespace wd
