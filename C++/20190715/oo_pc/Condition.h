#pragma once

#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class Condition
{
	public:
		//构造函数
		Condition(MutexLock & mutex)
		: _mutex(mutex)
		{
			//初始化条件变量
			if(pthread_cond_init(&_cond,nullptr)){
				perror(">>pthread_cond_init");
			}
		}

		//睡在条件变量函数
		void wait()
		{
			if(pthread_cond_wait(&_cond,_mutex.getMutexLockPtr())){
				perror(">>pthread_cond_wait");
			}
		}

		//单个唤醒函数
		void notify()
		{
			if(pthread_cond_signal(&_cond)){
				perror(">>pthread_cond_signal");
			}
		}

		//群体唤醒函数
		void notifyAll()
		{
			if(pthread_cond_broadcast(&_cond)){
				perror(">>pthread_cond_broadcast");
			}
		}

		//析构函数
		~Condition()
		{
			//执行条件变量销毁函数
			if(pthread_cond_destroy(&_cond)){
				perror(">>pthread_cond_destroy");
			}
		}

	private:
		//数据成员
		pthread_cond_t _cond;//条件变量
		MutexLock & _mutex;//互斥锁
};

}//end of namespace wd
