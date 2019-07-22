#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数实现
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize) //初始化任务队列容量
, _mutex()          //调用MutexLock类型的无参构造函数
, _notFull(_mutex)  //调用Condition类型的构造函数
, _notEmpty(_mutex)
{}

//任务队列是否为空
bool TaskQueue::empty() const
{
	return _que.size()==0;
}

//任务队列是否已满
bool TaskQueue::full() const
{
	return _que.size()==_queSize;
}

//将任务放入任务队列
//运行在生产者线程，number为要放入任务队列的任务元素
void TaskQueue::push(int number)
{
	//MutexLockGuard类型为互斥锁保护类型，
	//创建对象同时上锁，销毁对象同时解锁
	MutexLockGuard autolock(_mutex);
	while(full()){
		//使用while是为了防止出现虚假唤醒，
		//因为会有单个唤醒时多个子线程同时被唤醒的情况
				
		//任务队列已满，则生产者线程睡在_notFull条件变量上
		_notFull.wait();
	}

	//此时将任务放入任务队列中
	_que.push(number);

	//唤醒睡在_notEmpty条件变量上的消费者线程
	_notEmpty.notify();
}

//将任务从任务队列中拿出
//运行在消费者线程，返回的是从任务队列中拿出的任务
int TaskQueue::pop()
{
	//RAII技术
	MutexLockGuard autolock(_mutex);
	while(empty()){
		//防止虚假唤醒
		
		//任务队列为空时，消费者线程睡在_notEmpty条件变量上
		_notEmpty.wait();
	}

	//任务元素
	int number=_que.front();
	_que.pop();

	//唤醒睡在_notFull条件变量上的生产者
	_notFull.notify();

	//返回拿出的任务
	return number;
}

}//end of namespace wd

