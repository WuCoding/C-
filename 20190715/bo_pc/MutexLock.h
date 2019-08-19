#pragma once

#include "Noncopyable.h"

#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class MutexLock
: Noncopyable //默认继承方式为private
{
public:
	MutexLock()
	: _isLocking(false)
	{
		//初始化互斥锁
		if(pthread_mutex_init(&_mutex,nullptr)){
			perror(">>pthread_mutex_init");
		}
	}

	//上锁
	void lock()
	{
		if(pthread_mutex_lock(&_mutex)){
			perror(">> pthread_mutex_lock");
		}

		_isLocking=true;
	}

	//解锁
	void unlock()
	{
		if(pthread_mutex_unlock(&_mutex)){
			perror(">> pthread_mutex_unlock");
		}
		_isLocking=false;
	}

	//判断是否已上锁
	bool isLocking() const
	{
		return _isLocking;
	}

	//获得互斥锁指针
	pthread_mutex_t *getMutexLockPtr()
	{
		return &_mutex;
	}

	//析构函数
	~MutexLock()
	{
		if(pthread_mutex_destroy(&_mutex)){
			perror(">>pthread_mutex_destroy");
		}
	}

private:
	//互斥锁
	pthread_mutex_t _mutex;
	//是否上锁标志位
	bool _isLocking;
};

//互斥锁保护类，创建对象时上锁，销毁对象时解锁
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock &mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		_mutex.unlock();
	}
private:
	MutexLock &_mutex;
};

}//end of namespace wd


