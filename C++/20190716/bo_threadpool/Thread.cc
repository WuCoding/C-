#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//线程开始函数
void Thread::start()
{
	//真正创建子线程的地方
	pthread_create(&_pthid,nullptr,threadfunc,this);
	_isRunning=true;
}

//线程函数
void *Thread::threadfunc(void arg)
{
	//强制类型转换，传给子线程的线程函数参数为指向Thread对象的指针
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){//传入的参数不为空
		pthread->_cb();
	}
	return nullptr;
}

//线程回收函数
void Thread::join()
{
	if(_isRunning){//将线程join()
		pthread_join(_pthid,nullptr);
	}
}

//析构函数
Thread::~Thread()
{
	if(_isRunning){
		pthread_detach(_pthid);
	}
}

}//end of namespace wd
