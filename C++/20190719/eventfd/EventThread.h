#pragma once

#include "Thread.h"
#include "Eventfd.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class EventThread
{
	using EventCallback=function<void()>;

	public:
		//构造函数
		EventThread(EventCallback && cb)
		: _eventfd(std::move(cb))  
		//调用Eventfd类型的构造函数，该回调函数为eventfd描述符可读时执行的操作
		, _thread(std::bind(&Eventfd::start,&_eventfd))
		//调用Thread的构造函数，传入回调函数，作为线程函数中实际执行的操作
		//start用来监听eventfd的可读事件，如果可读执行Eventfd类型中的回调函数
		{}

		void start()
		{
			//调用线程对象的start()函数，创建子线程并传入回调函数
			_thread.start();
		}

		void wakeup()
		{
			//调用Eventfd类型的wakeup()函数，将eventfd中的counter计数器
			//上加8字节整数
			_eventfd.wakeup();
		}

		void stop()
		{
			//将标志位置为false
			_eventfd.stop();
			//将线程回收函数
			_thread.join();
		}

	private:
		Eventfd _eventfd;
		Thread _thread;
};
}//end of namespace wd

