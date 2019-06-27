#pragma once

#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;
//注意条件变量和锁并没有包含关系，即条件变量中不存在锁的数据成员，销毁时是分开销毁的，二者独立
namespace wd
{
	class Condition
	{
		public:
			//构造函数
			Condition( MutexLock & mutex)
			: _mutex(mutex)//初始化锁的引用
			{
				//初始化条件变量
				if(pthread_cond_init(&_cond,nullptr)){
					perror(">> pthread_cond_init");
				}
			}

			//睡眠函数
			void wait()
			{
				//传递条件变量和锁的地址
				if(pthread_cond_wait(&_cond,_mutex.getMutexLockPtr())){
					perror(">> pthread_cond_wait");
				}
			}

			//单个通知，很多线程睡在这个条件变量上，调用单个唤醒函数，只是将其中一个睡在该条件变量的线程进行唤醒
			void notify()
			{
				if(pthread_cond_signal(&_cond)){
					perror(">> pthread_cond_signal");
				}
			}

			//群体通知，很多线程睡在这个条件变量上，调用全部唤醒函数，将睡在该条件变量上的所有线程全部唤醒
			void notifyAll()
			{
				if(pthread_cond_broadcast(&_cond)){
					perror(">> pthread_cond_broadcast");
				}
			}

			//析构函数，销毁条件变量
			~Condition()
			{
				if(pthread_cond_destroy(&_cond)){
					perror(">> pthread_cond_destroy");
				}
			}
		private:
			pthread_cond_t _cond;
			MutexLock & _mutex;//在条件变量睡眠时，需要用到加解锁，这里有一个锁的引用
	};
}//end of namespace wd
	
