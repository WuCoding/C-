#pragma once

#include "Thread.h"
#include "Timerfd.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class TimerThread
{
	using TimerCallback=function<void()>;//默认权限为private
public:
	//构造函数
	TimerThread(int initialTime,int intervalTime,TimerCallback &&cb)
	: _timer(initialTime,intervalTime,std::move(cb))
	, _thread(std::bind(&Timer::start,&_timer))//一直监控timerfd，可读时执行回调函数
	{}

	void start()
	{
		_thread.start();//创建一个子线程，并传入线程函数
	}

	void stop()
	{
		_timer.stop();
		_thread.join();
	}
private:
	Timerfd _timer;
	Thread _thread;
};
}//end of namespace wd

