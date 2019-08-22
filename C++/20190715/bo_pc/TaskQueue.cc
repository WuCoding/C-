#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//任务队列构造函数实现
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{}

//判断任务队列是否为空
bool TaskQueue::empty() const
{
	return _que.size()==0;
}

//判断任务队列是否已满
bool TaskQueue::full() const
{
	return _que.size()==_queSize;
}

//运行在生产者线程，将任务加入到任务队列
void TaskQueue::push(int number)
{
	//上锁
	MutexLockGuard autolock(_mutex);
	while(full()){//使用while是为了防止出现虚假唤醒
		_notFull.wait();//异常（虚假）唤醒
	}

	_que.push(number);
	//唤醒睡在不空条件变量上的消费者线程
	_notEmpty.notify();
}

//运行在消费者线程，将任务从任务队列中取出
int TaskQueue::pop()
{
	//RAII技术
	MutexLockGuard autolock(_mutex);
	while(empty()){//防止虚假唤醒
		_notEmpty.wait();
	}
	//取任务
	int number=_que.front();
	_que.pop();

	//唤醒睡在不满条件变量上的生产者线程
	_notFull.notify();

	//返回任务
	return number;
}
}//end of namespace wd

