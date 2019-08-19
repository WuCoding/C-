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
	//构造函数传入互斥锁
	Condition(MutexLock &mutex)
	: _mutex(mutex)
	{
		//对条件变量进行初始化
		if(pthread_cond_init(&_cond,nullptr)){
			perror(">> pthread_cond_init");
		}
	}

	//将线程睡在该条件变量上
	void wait()
	{
		if(pthread_cond_wait(&_cond,_mutex.getMutexLockPtr())){
			perror(">> pthread_cond_wait");
		}
	}

	//单个线程唤醒函数
	void notify()
	{
		if(pthread_cond_signal(&_cond)){
			perror(">> pthread_cond_signal");
		}
	}

	//唤醒睡在该条件变量上的所有线程
	void notifyAll()
	{
		//广播
		if(pthread_cond_broadcast(&_cond)){
			perror(">> pthread_cond_broadcast");
		}
	}

	//析构函数，将条件变量销毁
	~Condition()
	{
		if(pthread_cond_destroy(&_cond)){
			perror(">> pthread_cond_destroy");
		}
	}
private:
	//条件变量
	pthread_cond_t _cond;
	//互斥锁引用
	MutexLock & _mutex;
};

}//end of namespace wd
