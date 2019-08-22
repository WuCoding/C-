#include "WorkerThread.h"

#include "Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

WorkerThread::WorkerThread(Threadpool & threadpool)
: _threadpool(threadpool)
{
	cout<<"WorkerThread()"<<endl;
}

WorkerThread::~WorkerThread()
{
	cout<<"~WorkerThread()"<<endl;
}

//执行线程函数
void WorkerThread::run()
{
	_threadpool.threadfunc();
}

}//end of namespace wd
	
