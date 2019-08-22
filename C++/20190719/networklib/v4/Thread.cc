#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//传递回调函数的构造函数
Thread::Thread(ThreadCallback &&cb)
: _pthid(0)
, _cb(std::move(cb))
, _isRunning(false)
{
	cout<<"Thread()"<<endl;
}

//线程开始函数
void Thread::start()
{
	//创建子线程，this指针作为线程函数的参数
	pthread_create(&_pthid,NULL,threadFunc,this);
	_isRunning=true;
}

//线程函数
void *Thread::threadFunc(void *arg)
{
	//强制类型转换
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){//如果pthread指针不为空
		//执行该对象注册的回调函数
		pthread->_cb();
	}
	return nullptr;
}

//线程回收函数
void Thread::join()
{
	if(_isRunning){//如果线程启动了，执行回收线程函数
		pthread_join(_pthid,NULL);
	}
}

//析构函数
Thread::~Thread()
{
	if(_isRunning){//如果线程启动了
		pthread_detach(_pthid);
	}
	cout<<"~Thread()"<<endl;
}
}//end of namespace wd






























