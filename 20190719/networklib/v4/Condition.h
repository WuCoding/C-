#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"

#include <pthread.h>

namespace wd
{

//类的前向声明 可以减少头文件的依赖
class MutexLock;

class Condition
: Noncopyable
{
	public:
		//构造函数
		Condition(MutexLock & mutex);
		//析构函数
		~Condition();

		void wait();
		void notify();
		void notifyAll();

	private:
		//条件变量
		pthread_cond_t _cond;
		//互斥锁
		MutexLock & _mutex;
};

}//end of namespace wd

#endif
