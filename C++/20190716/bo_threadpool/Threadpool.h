#pragma once

#include "TaskQueue.h"

#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace wd
{

class Thread;//前向声明，不需要知道该类的具体实现

class Threadpool
{
//友元类型声明
friend class WorkerThread;

public:
	//构造函数，传入子线程数目(默认为4个子线程)，任务队列长度(默认任务队列长度为10)
	Threadpool(size_t threadNum=4,size_t queSize=10);
	~Threadpool();

	//线程池开始函数
	void start();
	void addTask(Task &&task);//向任务队列添加任务函数
	
	void stop();
private:
	//从任务队列中取任务
	Task getTask();
	//线程函数
	void threadfunc();
private:
	//数据成员
	size_t _threadNum;//子线程个数
	size_t _queSize;//任务队列长度
	vector<unique_ptr<Thread>> _threads;//存放子线程指针的vector容器
	TaskQueue _taskque;//任务队列
	bool _isExit;//线程池是否退出标志
};

}//end of namespace wd

