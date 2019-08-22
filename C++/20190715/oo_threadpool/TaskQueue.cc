#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)//赋值任务队列的长度
, _mutex()//调用MutexLock类型的无参构造函数
, _notFull(_mutex)//调用Condition类型的构造函数
, _notEmpty(_mutex)//调用Condition类型的构造函数
, _flag(true)
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

//运行在生产者线程，生产函数，负责向任务队列中添加任务
void TaskQueue::push(ElemType & elem)//传入的是Task类型的指针
{
	//先上锁，用互斥锁保护类
	MutexLockGuard autolock(_mutex);
	while(full()){//使用while是为了防止出现虚假唤醒
		_notFull.wait();//异常（虚假）唤醒
	}

	//能走到这里说明队列已经不满
	_que.push(elem);

	//唤醒睡在不空条件变量上的消费者线程
	_notEmpty.notify();
	//互斥锁保护类对象生命周期结束，互斥锁解锁
}

//运行在消费者线程，消费函数，负责从任务队列中取任务
ElemType TaskQueue::pop()
{
	//RAII技术
	//也称为“资源获取就是初始化”，是c++等编程语言常用的管理资源、避免内存泄露的方法。
	//它保证在任何情况下，使用对象时先构造对象，最后析构对象。
	MutexLockGuard autolock(_mutex);
	while(_flag && empty()){//防止虚假唤醒，条件变量在使用且任务队列为空
		_notEmpty.wait();
	}

	if(_flag){//走到这里说明，条件变量在使用中，任务队列不为空
		//从任务队列中拿任务
		ElemType elem=_que.front();
		_que.pop();

		_notFull.notify();

		return elem;
	}else{//走到这里说明该条件变量已经wakeup()，_flag已经置为false
		return nullptr;
	}
}

void TaskQueue::wakeup()
{
	_flag=false;
	//将睡在_notEmpty条件变量上的所有消费者线程都唤醒
	_notEmpty.notifyAll();
}

}//end of namespace wd







