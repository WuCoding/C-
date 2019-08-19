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
: Noncopyable
{
public:
	MutexLock()
	: _isLocking(false)
	{
		//互斥锁的初始化
		if(pthread_mutex_init(&_mutex,nullptr)){
			perror(">> pthread_mutex_init");
		}
	}

	//上锁
	void lock()
	{
		if(pthread_mutex_lock(&_mutex)){
			perror(">>pthread_mutex_lock");
		}
		_isLocking=true;
	}

	//解锁
	void unlock()
	{
		if(pthread_mutex_unlock(&_mutex)){
			perror(">>pthread_mutex_unlock");
		}
		_isLocking=false;
	}

	//判断是否上锁
	bool isLocking() const
	{
		return _isLocking;
	}

	//获得互斥锁的指针
	pthread_mutex_t *getMutexLockPtr()
	{
		return &_mutex;
	}

	~MutexLock()
	{
		//销毁该互斥锁
		if(pthread_mutex_destroy(&_mutex)){
			perror(">>pthread_mutex_destroy");
		}
	}
private:
	pthread_mutex_t _mutex;
	bool _isLocking;
};

//互斥锁保护类，数据成员为互斥锁对象的引用
//创建对象时上锁，销毁对象时解锁
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock &_mutex)
	: _mutex(mutex)
	{
		//上锁
		_mutex.lock();
	}

	~MutexLockGuard()
	{
		//解锁
		_mutex.unlock();
	}
private:
	MutexLock &_mutex;
};

}//end of namespace wd
