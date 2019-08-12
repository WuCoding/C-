#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "TaskQueue.h"
#include "Thread.h"

#include <vector>
#include <memory>
#include <functional>
using std::vector;
using std::unique_ptr;

namespace wd
{

//任务类型
using Task=std::function<void()>;
class ThreadPool
{
public:
	//构造函数
	ThreadPool(size_t,size_t);

	//线程池开始函数
	void start();
	//线程池结束函数
	void stop();

	//往任务队列添加任务函数
	void addTask(Task && task);
private:
	//子线程函数
	void threadFunc();
	//获得任务函数
	Task getTask();
private:
	//数据成员
	size_t _threadNum;//子线程数
	size_t _queSize;//任务队列长度
	vector<unique_ptr<Thread>> _threads;//存储子线程对象指针的容器
	TaskQueue _que;//任务队列
	bool _isExit;//是否已退出线程池的标志位
};

}//end of namespace wd

#endif
