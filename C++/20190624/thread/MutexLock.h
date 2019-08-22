#pragma once

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
	class MutexLock
	{
		public:
			//构造函数
			MutexLock()
			: _isLocking(false)
			{
				if(pthread_mutex_init(&_mutex,nullptr)){//初始化锁
					perror(">> pthread_mutex_init");
				}
			}
			//C++11 用法，表示禁止使用该函数，相当于将这个函数删除掉了
			//因为在实际使用锁的情景中，没有锁的复制和赋值，所以将这两
			//个函数删除掉，不能再使用
			//复制构造函数
			MutexLock(const MutexLock &)=delete;
			//赋值运算符重构函数
			MutexLock & operator=(const MutexLock &)=delete;

			//上锁函数
			void lock()
			{
				if(pthread_mutex_lock(&_mutex)){//对锁进行上锁
					perror(">> pthread_mutex_lock");
				}
				//将上锁标志位置为 true
				_isLocking=true;
			}

			//解锁函数
			void unlock()
			{
				if(pthread_mutex_unlock(&_mutex)){//对锁进行解锁
					perror(">> pthread_mutex_unlock");
				}
				//将锁的标志位置为 false
				_isLocking=false;
			}

			//查询是否上锁
			bool isLocking() const //不改变数据成员的成员函数都设为const，这样常量对象和非常量对象都可以调用
			{
				return _isLocking;
			}

			//获得锁的地址，为的是在条件变量类里上锁时用的是MutexLock对象数据成员_mutex锁的地址，而不是MutexLock对象的地址，两个地址是不同的
			pthread_mutex_t * getMutexLockPtr()
			{
				return &_mutex;
			}

			//析构函数
			~MutexLock()
			{
				//调用锁的销毁函数
				if(pthread_mutex_destroy(&_mutex)){
					perror(">> pthread_mutex_destroy");
				}
			}
#if 0
		//禁止复制==》对象语义
		//可以复制==》值语义
		private:
			MutexLock(const MutexLock&);
			MutexLock & operator=(const MutexLock &);
#endif
		private:
			pthread_mutex_t _mutex;
			bool _isLocking;//有无上锁的标志，true为上锁，false为未上锁
	};

	//锁的保护类，防止因意外导致未解锁而退出线程，造成其他线程无法解锁
	//创建该类的对象时，自动上锁，因为是局部对象，生命期结束时，自动调用析构函数，自动解锁
	class MutexLockGuard
	{
		public:
			//构造函数，自动进行上锁
			MutexLockGuard(MutexLock & mutex)
			: _mutex(mutex)
			{
				//创建锁保护类的对像的同时，进行上锁
				_mutex.lock();
			}

			//析构函数，在析构函数中进行解锁
			~MutexLockGuard()
			{
				_mutex.unlock();
			}
		private:
			MutexLock & _mutex;//数据成员是锁的引用
	};
}//end of namespace wd
