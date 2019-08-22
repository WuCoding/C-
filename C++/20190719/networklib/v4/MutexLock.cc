#include "MutexLock.h"

#include <stdio.h>
#include <errno.h>

namespace wd
{

//构造函数
MutexLock::MutexLock()
: _isLocking(false)
{
	//创建一个互斥锁
	if(pthread_mutex_init(&_mutex,NULL)){
		perror("pthread_mutex_init");
	}
}

//析构函数
MutexLock::~MuteLock()
{
	//销毁该互斥锁
	if(pthread_mutex_destroy(&_mutex)){
		perror("pthread_mutex_destroy");
	}
}

//上锁
void MutexLock::lock()
{
	if(pthread_mutex_lock(&_mutex)){
		perror("pthread_mutex_lock");
		return;
	}
	_isLocking=true;
}

//解锁
void MutexLock::unlock()
{
	if(pthread_mutex_unlock(&_mutex)){
		perror("pthread_mutex_unlock");
		return;
	}
	_isLocking=false;
}

}//end of namespace wd

































