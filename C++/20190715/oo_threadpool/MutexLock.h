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
: Noncopyable //class类默认继承方式为private
{
public:
	//构造函数，初始化互斥锁
	MutexLock()
	: _isLocking(false)
	{
		//初始化互斥锁
		if(pthread_mutex_init(&_mutex,nullptr)){
			perror(">> pthread_mutex_init");
		}
	}

	//进行上锁操作
	void lock()
	{
		//进行上锁
		if(pthread_mutex_lock(&_mutex)){
			perror(">>pthread_mutex_lock");
		}
		_isLocking=true;
	}

	//进行解锁操作
	void unlock()
	{
		if(pthread_mutex_unlock(&_mutex)){
			perror(">>pthread_mutex_unlock");
		}
		_isLocking=false;
	}

	//返回是否上锁
	bool isLocking() const
	{
		return _isLocking;
	}

	//返回互斥锁的地址指针
	pthread_mutex_t * getMutexLockPtr()
	{
		return &_mutex;
	}

	//析构函数，销毁互斥锁
	~MutexLock()
	{
		if(pthread_mutex_destroy(&_mutex)){
			perror(">> pthread_mutex_destroy");
		}
	}

private:
	//数据成员
	pthread_mutex_t _mutex;//创建了的互斥锁
	bool isLocking;//是否上锁的标志位
};

//互斥锁保护类，数据成员只有一个互斥锁的引用
//保护类对象创建时上锁，销毁时解锁
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
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
	
