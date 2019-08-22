#pragma once

#include "TaskQueue.h"

#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

namespace wd
{

class Task;
class Thread;

class Threadpool
{
//友元类的声明
friend class WokerThread;
public:
	Threadpool(size_t threadNum=4, size_t queSize=10);
	~Threadpool();

	void start();
	void addTask(Task *task);

	void stop();
private:
	Task *getTask();
	void threadfunc();
private:
	size_t _threadNum;//子线程数量
	size_t _queSize;//任务队列长度
	vector<unique_ptr<Thread>> _threads;//存放子线程指针的容器
	TaskQueue _taskque;//任务队列
	bool _isExit;//是否退出标志位
};

}//end of namespace wd
