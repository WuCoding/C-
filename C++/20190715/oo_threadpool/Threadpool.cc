#include "Threadpool.h"
#include "WorkerThread.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//线程池构造函数
Threadpool::Threadpool(size_t threadNum,size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskque(queSize)
, _isExit(false)
{
	//_threads是vector容器，用来存放创建的子线程的指针
	_threads.reserve(_threadNum);//先将容器的空间进行扩充
}

//析构函数
Threadpool::~Threadpool()
{
	if(!_isExit){//_isExit为false
		stop();
	}
}

//线程池开始函数
void Threadpool::start()
{
	//依次创建子线程对象，并将指针压入存放子线程指针的vector容器中
	for(size_t idx=0;idx!=_threadNum;++idx){
		unique_ptr<Thread> thread(new WorkerThread(*this));//将线程池的this指针传给子线程
		_threads.push_back(std::move(thread));//将指针压入到vector容器中
		//_threads.push_back(thread);
	}

	//真正创建出子线程
	for(auto & thread: _threads){
		thread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit){//_isExit为false

		//等待任务队列变为空
		while(!_taskque.empty()){
			::sleep(1);
		}

		_isExit=true;
		//将睡在条件变量上的消费者线程唤醒，以用来join()，不然会出现死锁
		_taskque.wakeup();
		for(auto & thread:_threads){
			thread->join();//依次将子线程进行回收
		}
	}
}

//添加任务
void Threadpool::addTask(Task *task)
{
	_taskque.push(task);
}

//从任务队列获取任务
Task *Threadpool::getTask()
{
	return _taskque.pop();
}

//每一个消费者线程要完成的任务，其运行在WorkerThread::run方法中
void Threadpool::threadfunc()
{
	while(!_isExit){//_isExit标志位为false，线程池未退出
		//从任务队列拿任务
		Task *task=getTask();
		if(task){//如果成功拿到了任务
			task->process();
			//当任务执行的速度过快，在还没有将_isExit设置为true之前，
			//每一个子线程已经阻塞在了getTask()方法上
		}
	}
}

}//end of namespace wd



