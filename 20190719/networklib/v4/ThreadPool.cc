#include "ThreadPool.h"
#include "Thread.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数
ThreadPool::ThreadPool(size_t threadNum,size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _que(_queSize)//调用TaskQueue类型的构造函数
, _isExit(false)//是否退出的标志位
{
	//vector<unique_ptr<Thread>>类型的容器
	_threads.reserve(_threadNum);//先将容器扩充空间
}

//将线程池启动
void ThreadPool::start()
{
	//依次创建子线程对象将线程池的this指针作为线程函数的参数
	for(size_t idx=0;idx!=_threadNum;++idx){
		unique_ptr<Thread> thread(new Thread(
			std::bind(&Threadpool::threadFunc,this)
		));
		//将该线程指针转移到线程容器中
		_threads.push_back(std::move(thread));
	}

	//依次启动子线程
	for(auto &thread: _threads){
		thread->start();//此步骤才是真正的创建了子线程，之前那一步只是创建子线程对象
	}
}

//线程池停止函数
void ThreadPool::stop()
{
	if(!_isExit){//如果退出标志位为false
		//先将任务队列中的任务执行完毕
		while(!_que.empty()){
			//任务队列不为空时，就睡1s直到任务队列为空
			::sleep(1);
		}

		//将退出标志位置为true
		_isExit=true;
		cout<<">>> _isExit=true"<<endl;

		//将消费者线程全部唤醒，因为要回收他们，一直睡着就join不成功
		_que.wakeup();

		//依次回收子线程
		for(auto & thread: _threads){
			thread->join();
		}
	}
}

//向任务队列中添加任务
void ThreadPool::addTask(Task && task)
{
	_que.push(task);
}

//从任务队列中获得任务
Task ThreadPool::getTask()
{
	return _que.pop();
}

//子线程执行的函数
void ThreadPool::threadFunc()
{
	while(!_isExit){
		//如果退出标志位为false，从任务队列中拿任务
		Task task=getTask();
		if(task){//如果task不为空，执行task任务
			task();
		}
	}
}

}//end of namespace wd


