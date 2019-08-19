#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

void Thread::start()
{
	//创建线程
	pthread_create(&_pthid,nullptr,threadfunc,this);
	_isRunning=true;
}

void *Thread::threadfunc(void *arg)
{
	//强制类型转换
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){//如果pthread存在
		//执行run()函数
		pthread->run();
	}
	return nullptr;
}

//线程回收函数
void Thread::join()
{
	if(_isRunning){//如果该子线程已经启动
		pthread_join(_pthid,nullptr);//将该子线程进行回收
	}
}

//析构函数
Thread::~Thread()
{
	if(_isRunning){//如果该子线程已经运行
		pthread_detach(_pthid);
	}
}
}//end of namespace wd
