#ifndef __WD_MUTEXLOCK_H__
#define __WD_MUTEXLOCK_H__

#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{

class MutexLock
: Noncopyable //默认以private方式继承
{
	public:
		//构造函数
		MutexLock();
		//析构函数
		~MutexLock();

		//上锁操作
		void lock();
		//解锁操作
		void unlock();

		//获得互斥锁指针
		pthread_mutex_t* getMutexLockPtr()
		{
			return &_mutex;
		}

	private:
		//是否上锁标志位
		bool _isLocking;
		//互斥锁
		pthread_mutex_t _mutex;
};

//互斥锁保护类
class MutexLockGuard
{
	//创建保护类对象时上锁，销毁保护类对象时解锁
	public:
		//构造函数
		MutexLockGuard(MutexLock & mutex)
		: _mutex(mutex)
		{
			//上锁
			_mutex.lock();
		}

		//析构函数
		~MutexLockGuard()
		{
			//解锁
			_mutex.unlock();
		}
	private:
		MutexLock &_mutex;
};
}//end of namespace wd

#endif

