#pragma once

#include "Noncopyable.h"

#include <pthread.h>

#include <functional>
#include <string>
using std::function;
using std::string;

namespace wd
{
	
namespace current_thread
{
//声明
extern __thread const char *threadName;
}//end of namespace current_thread

//具体类
class Thread
: Noncopyable //默认为private方式继承
{
	public:
		using ThreadCallback=function<void()>;

		//构造函数
		Thread(ThreadCallback &&cb,const string &name=string())
		: _pthid(0)
		, _isRunning(false)
		, _cb(std::move(cb))
		, _name(name)
		{}

		void start();
		void join();

		string getName() const
		{
			return _name;
		}

		~Thread();

	private:
		static void *threadfunc(void *arg);
	private:
		pthread_t _pthid;
		bool _isRunning;
		ThreadCallback _cb;
		string _name;
};
}//end of namespace wd


