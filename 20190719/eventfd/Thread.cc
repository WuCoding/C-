#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//创建一个线程，将运行标志位设为true
void Thread::start()
{
	//将this指针作为线程函数参数
	pthread_create(&_pthid,nullptr,threadfunc,this);
	_isRunning=true;
}

//线程函数
void * Thread::threadfunc(void *arg)
{
	//进行强制类型转换
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){
		//执行回调函数
		pthread->_cb();
	}
	return nullptr;
}

//回收线程函数
void Thread::join()
{
	if(_isRunning){//如果线程已经创建
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
