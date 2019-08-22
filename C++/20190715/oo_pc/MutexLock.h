#pragma once

#include "Noncopyable.h"

#include <stdio.h>
#include <error.h>
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class MutexLock
: Noncopyable
{
	public:
		//构造函数
		MutexLock()
		: _isLocking(false)
		{
			//对互斥锁进行初始化
			if(pthread_mutex_init(&_mutex,nullptr)){
				perror(">>pthread_mutex_init");
			}
		}

		//上锁操作
		void lock()
		{
			if(pthread_mutex_lock(&_mutex)){
				perror(">>pthread_mutex_lock");
			}
			_isLocking=true;
		}

		//解锁操作
		void unlock()
		{
			if(pthread_mutex_unlock(&_mutex)){
				perror(">>pthread_mutex_unlock");
			}
			_isLocking=false;
		}

		//查询是否上锁
		bool isLocking() const
		{
			return _isLocking;
		}

		//获得互斥锁的指针
		pthread_mutex_t* getMutexLockPtr()
		{
			return &_mutex;
		}

		//析构函数
		~MutexLock()
		{
			//执行互斥锁销毁函数
			if(pthread_mutex_destroy(&_mutex)){
				perror(">>pthread_mutex_destroy");
			}
		}
	private:
		//数据成员
		pthread_mutex_t _mutex;//互斥锁
		bool _isLocking;//标志位，是否已上锁
};


//创建对象时直接上锁，对象生命周期结束时自动解锁
class MutexLockGuard
{
	public:
		//构造函数，创建对象时直接上锁
		MutexLockGuard(MutexLock & mutex)
		: _mutex(mutex)
		{
			_mutex.lock();
		}

		//析构函数，销毁对象时直接解锁
		~MutexLockGuard()
		{
			_mutex.unlock();
		}
	private:
		//数据成员
		MutexLock & _mutex;//互斥锁的引用
};

}//end of namespace wd


































