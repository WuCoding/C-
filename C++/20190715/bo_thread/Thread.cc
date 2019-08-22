#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

void Thread::start()
{
	pthread_create(&_pthid,nullptr,threadfunc,this);
	_isRunning=true;
}

void * Thread::threadfunc(void *arg)
{
	//进行类型转换
	Thread * pthread=static_cast<Thread*>(arg);
	if(pthread){//pthread不为空
		pthread->_cb();//执行回调函数
	}

	return nullptr;
}

//回收线程
void Thread::join()
{
	if(_isRunning){
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
