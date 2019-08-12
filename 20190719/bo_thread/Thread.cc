#include "Thread.h"

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

namespace wd
{

namespace current_thread
{
	__thread const char *threadName="wd thread";
}

//ThreadData结构体，默认成员权限为public
struct ThreadData
{
	using ThreadCallback=function<void()>;

	//构造函数
	ThreadData(const string & name,ThreadCallback &&cb)
	: _name(name)
	, _cb(std::move(cb))
	{}

	//数据成员：
	//线程名称：
	string _name;
	//线程回调函数：
	ThreadCallback _cb;

	void runInThread()
	{
		//如果name为无参string对象，线程名称设为"wd thread"，否则赋值为name的字符串
		current_thread::threadName=_name==string()?"wd thread":_name.c_str();
		if(_cb){//如果注册回调函数则执行回调函数
			_cb();
		}
	}
};

void Thread::start()
{
	//将本线程对象的数据成员传递给ThreadData
	ThreadData *threadData=new ThreadData(_name,std::move(_cb));

	//创建一个线程，将ThreadData对象作为参数传递给子线程
	pthread_create(&_pthid,nullptr,threadfunc,threadData);

	//设置标志位为启动
	_isRunning=true;
}

//线程函数
void *Thread::threadfunc(void* arg)
{
	//强制类型转换
	ThreadData * threadData=static_cast<ThreadData*>(arg);
	if(threadData){
		//执行ThreaData对象的runInThread()函数，实际执行的是线程的回调函数
		threadData->runInThread();
	}

	//执行完回调函数，回收ThreadData堆对象空间
	delete threadData;

	return nullptr;
}

//回收函数
void Thread::join()
{
	if(_isRunning){//如果线程已经启动
		pthread_join(_pthid,nullptr);
	}
}

//析构函数
Thread::~Thread()
{
	if(_isRunning){//如果线程已经启动
		pthread_detach(_pthid);
	}
}
}//end of namespace wd





























