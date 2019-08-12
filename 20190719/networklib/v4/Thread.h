#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include "Noncopyable.h"

#include <pthread.h>

#include <functional>

namespace wd
{

class Thread
: Noncopyable
{
	public:
		using ThreadCallback=std::function<void()>;
		
		//构造函数
		Thread(ThreadCallback &&cb);

		void start();
		void join();

		//析构函数
		~Thread();
	private:
		static void *threadFunc(void *);
	private:
		//线程id
		pthread_t _pthid;
		//回调函数
		ThreadCallback _cb;
		//运行标志位
		bool _isRunning;
};

}//end of namespace wd

#endif
	
