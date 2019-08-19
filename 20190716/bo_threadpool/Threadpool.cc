#include "Threadpool.h"
#include "Thread.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//线程池构造函数
Threadpool::Threadpool(size_t threadNum,size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize) //任务队列长度
, _taskque(queSize)  //调用TaskQueue类型的构造函数
, _isExit(false)
{
	//将存储子线程指针的vector容器扩容
	_threads.reserve(_threadNum);
}

//析构函数
Threadpool::~Threadpool()
{
	if(!_isExit){//没有退出
		stop();
	}
}

//线程池开始函数，创建子线程
void Threadpool::start()
{
	for(size_t idx=0;idx!=_threadNum;++idx){
		unique_ptr<Thread> thread(new Thread(
			std::bind(&Threadpool::threadfunc,this)			
		));
		//将线程的指针压入vector容器中
		_threads.push_back(std::move(thread));
	}

	//依次循环创建子线程
	for(auto &thread: _threads){
		thread->start();//真正执行pthread_create()函数的地方
	}
}

//线程池停止函数
void Threadpool::stop()
{
	if(!_isExit){
		//等将任务队列中的任务执行完
		while(!_taskque.empty()){
			::sleep(1);
		}

		_isExit=true;
		_taskque.wakeup();
		for(auto &thread: _threads){
			thread->join();
		}
	}
}

//向任务队列添加任务，运行在生产者线程
void Threadpool::addTask(Task &&task)
{
	_taskque.push(task);
}

//从任务队列中获取任务
Task Threadpool::getTask()
{
	return _taskque.pop();
}

//每一个子线程要完成的任务，其运行在WorkThread::run方法中
void Threadpool::threadfunc()
{
	//实际执行的操作就是如果没有退出就一直从任务队列中拿任务
	while(!_isExit)
	{
		Task task=getTask();
		if(task){//如果任务存在，执行任务
			task();
		}
		//当任务执行的速度过快，在还没有将_isExit设置为true之前，
		//每一个子线程已经阻塞在了getTask()方法之上
	}
}

}//end of namespace wd


