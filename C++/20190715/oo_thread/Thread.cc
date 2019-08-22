#include "Thread.h"

#include <iostream>
using std::cout;
using std::endl;
//该文件为Thread类型的具体实现
namespace wd
{
//Thread类型的函数的具体实现

//线程开始函数	
void Thread::start()
{
	//创建一个线程
	pthread_create(&_pthid,nullptr,threadfunc,this);//线程函数为Thread类型的成员函数
	//改变线程对象的标志位
	_isRunning=true;
}

//线程函数实现
void * Thread::threadfunc(void * arg)//参数传递的是该对象的this指针
{
	//类型转换，将void*类型转换为Thread*
	Thread *pthread=static_cast<Thread*>(arg);
	if(pthread){//如果pthread指针不为空则执行运行函数
		pthread->run();//run()函数为纯虚函数
	}

	//不需要返回什么指针，就返回个nullptr
	return nullptr;
}

//回收线程函数实现
void Thread::join()
{
	if(_isRunning){//说明子线程已经创建
		//回收子线程
		pthread_join(_pthid,nullptr);
	}
}

//析构函数（虚函数）
Thread::~Thread()
{
	if(_isRunning){//子线程已经创建
		//相当于将该_pthid加入到自动销毁的队列中，
		//不需要程序员主动调用join函数来销毁
		pthread_detach(_pthid);
	}
}
}//end of namespace wd
