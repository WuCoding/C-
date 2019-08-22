#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数，创建一个任务队列，默认长度为10
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _mutex() //调用MutexLock类型的默认构造函数
, _notFull(_mutex)
, _notEmpty(_mutex)
, _flag(true)
{}

//判断一个队列是否为空
bool TaskQueue::empty() const
{
	return _que.size()==0;
}

//判断一个队列是否已满
bool TaskQueue::full() const
{
	return _que.size()==_queSize;
}

//向任务队列加任务，运行在生产者线程
void TaskQueue::push(ElemType &elem)
{
	//互斥锁保护类，创建对象时自动上锁，销毁对象时解锁
	MutexLockGuard autolock(_mutex);
	while(full()){//使用while是为了防止出现虚假唤醒
		//睡在不满的条件变量上
		_notFull.wait();
	}

	//走到这里说明任务队列不满，可以往任务队列中放任务
	_que.push(elem);

	//唤醒消费者线程来取任务
	_notEmpty.notify();
}

//从任务队列中取任务，运行在消费者线程
ElemType TaskQueue::pop()
{
	//RAII技术
	MutexLockGuard autolock(_mutex);
	while(_flag && empty()){
		_notEmpty.wait();
	}

	//走到这里要么就是_flag=false(任务队列结束)，
	//要么就是_flag=true(任务队列未结束)，empty()=false(任务队列不空)
	if(_flag){//任务队列仍在运行，只是任务队列不为空
		//消费者线程从任务队列中拿任务
		ElemType elem=_que.front();
		_que.pop();

		//唤醒生产者线程进行生产任务
		_notFull.notify();

		return elem;
	}else{//任务队列已经结束，将睡在条件变量上的消费者线程唤醒，以来join()
		return nullptr;//此时已经没有任务了，不需要返回任务，只需返回个空指针即可
	}
}

//将睡在条件变量上的消费者全部唤醒以来join()
void TaskQueue::wakeup()
{
	_flag=false;
	_notEmpty.notifyAll();
}

}//end of namespace wd

