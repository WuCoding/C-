#include "Condition.h"
#include "MutexLock.h"

#include <stdio.h>
#include <errno.h>

namespace wd
{

//传入互斥锁的条件变量
Condition::Condition(MutexLock &mutex)
: _mutex(mutex)
{
	//构造条件变量
	if(pthread_cond_init(&_cond,NULL)){
		perror("pthread_cond_init");
	}
}

//析构函数
Condition::~Condition()
{
	//销毁条件变量
	if(pthread_cond_destroy(&_cond)){
		perror("pthread_cond_destroy");
	}
}


void Condition::wait()
{
	//睡在该条件变量上
	if(pthread_cond_wait(&_cond,_mutex.getMutexLockPtr())){
		perror("pthread_cond_wait");
	}
}

//唤醒一个线程
void Condition::notify()
{
	if(pthread_cond_signal(&_cond)){
		perror("pthread_cond_signal");
	}
}

//唤醒所有线程
void Condition::notifyAll()
{
	//广播
	if(pthread_cond_broadcast(&_cond)){
		perror("pthread_cond_broadcast");
	}
}

}//end of namespace wd
