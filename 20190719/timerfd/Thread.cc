#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//创建新的线程并将标志位置为true
void Thread::start()
{
	pthread_create(&_pthid,nullptr,threadfunc,this);
	_isRunning=true;
}

//子线程的线程函数实际执行的是回调函数
void * Thread::threadfunc(void *arg)
{
	//将传入参数指针进行强制类型转换，该指针为Thread对象的指针
	Thread * pthread=static_cast<Thread*>(arg);
	if(pthread){//如果pthread不为空
		//调用该对象的回调函数
		pthread->_cb();
	}

	return nullptr;
}

//回收函数
void Thread::join()
{
	if(_isRunning){//如果该子线程已经创建
		//对该子线程进行回收
		pthread_join(_pthid,nullptr);
	}
}

//析构函数
Thread::~Thread()
{
	if(_isRunning){//如果该线程已经运行
		pthread_detach(_pthid);
	}
}

}//end of namespace wd



