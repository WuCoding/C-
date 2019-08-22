#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
//线程启动函数
void Thread::start()
{
	//创建子线程
	pthread_create(&_pthid,nullptr,threadfunc,this);
	//改变线程启动标志位
	_isRunning=true;
}

//子线程执行函数
void * Thread::threadfunc(void *arg)//传入参数为this指针
{
	//将传入参数强制类型转换
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){
		//执行回调函数
		pthread->_cb();
	}

	return nullptr;
}

//线程回收函数
void Thread::join()
{
	if(_isRunning){//该线程已经启动
		pthread_join(_pthid,nullptr);
	}
}

//析构函数实现
Thread::~Thread()
{
	if(_isRunning){
		pthread_detach(_pthid);
	}
}
}//end of namespace wd
