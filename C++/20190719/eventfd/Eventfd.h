#pragma once

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

namespace wd
{

class Eventfd
{
	public:
		//void()类型的回调函数
		using EventCallback=function<void()>;

		//构造函数
		Eventfd(EventCallback && cb);

		void start();//运行在B线程
		void stop();

		void wakeup();//运行在A线程

	private:
		int createEventfd();
		void handleRead();
	private:
		int _fd;
		EventCallback _cb;
		bool _isStarted;
};
}//end of namespace wd
