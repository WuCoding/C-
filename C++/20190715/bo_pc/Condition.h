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
	Condition(MutexLock & mutex)
	: _mutex(mutex)
	{
		//初始化条件变量
		if(pthread_cond_init(&_cond,nullptr)){
			perror(">> pthread_cond_init");
		}
	}

	//让线程睡在条件变量上
	void wait()
	{
		if(pthread_cond_wait(&_cond,_mutex.getMutexLockPtr())){
			perror(">>pthread_cond_wait");
		}
	}

	//唤醒单个线程
	void notify()
	{
		if(pthread_cond_signal(&_cond)){
			perror(">>pthread_cond_signal");
		}
	}

	//唤醒全部线程
	void notifyAll()
	{
		if(pthread_cond_broadcast(&_cond)){
			perror(">> pthread_cond_broadcast");
		}
	}

	//析构函数
	~Condition()
	{
		//销毁条件变量
		if(pthread_cond_destroy(&_cond)){
			perror(">>pthread_cond_destroy");
		}
	}
private:
	//数据成员
	pthread_cond_t _cond;
	//互斥锁的引用
	MutexLock & _mutex;
};
}//end of namespace wd
