#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数，只传递一个任务队列的大小
TaskQueue::TaskQueue(size_t sz)
: _sz(sz)
, _mutex()//调用MutexLock类的无参构造函数，获得一个互斥锁
, _notEmpty(_mutex)//调用Condition类的构造函数
, _notFull(_mutex)//调用Condition类的构造函数
, _flag(true)
{}

//判断任务队列是否为空
bool TaskQueue::empty() const
{
	return _que.empty();
}

//判断任务队列是否已满
bool TaskQueue::full() const
{
	return _que.size()==_sz;
}

//将任务加入到任务队列中，该函数在生产者线程中运行
void TaskQueue::push(ElemType elem)
{
	{
		//互斥锁的保护类对象，创建对象时上锁，销毁时解锁
		MutexLockGuard autoLock(_mutex);
		while(full()){//如果任务队列已满，那么让该线程睡在不满时被唤醒的条件变量上
			//用while是为了防止条件变量被异常唤醒
			_notFull.wait();
		}
		//走到这里说明任务队列不满，将任务加入到任务队列中
		_que.push(elem);
	}
	//走到这时，互斥锁保护类的对象生命周期结束，此时互斥锁已解锁
	//将睡在不空条件变量上的线程（消费者线程）唤醒
	_notEmpty.notify();
}

//取任务函数，运行在消费者线程，该函数的返回值为任务，即线程执行的函数
ElemType TaskQueue::pop()
{
	ElemType ret;
	{
		//互斥锁保护类的对象，创建时自动上锁
		MutexLockGuard autoLock(_mutex);
		while(_flag && empty()){//如果任务队列还在执行中，且任务队列为空
			_notEmpty.wait();//睡在非空的条件变量上
		}
		if(_flag){//此时任务队列在执行中，且任务队列非空
			//取任务
			ret=_que.front();
			_que.pop();
			//将睡在不满的条件变量上的生产者线程唤醒
			_notFull.notify();
		}else{//此时任务队列已被销毁
			return nullptr;//因为任务元素就是一个函数指针，此时返回一个空指针
		}
	}//此处互斥锁保护类对象的生命周期已结束，已将锁解开
	//返回任务
	return ret;
}

//任务队列结束，将标志位置为false，并将所有消费者线程唤醒，将任务拿完
void TaskQueue::wakeup()
{
	//将标志位置为false
	_flag=false;
	//将消费者线程全部唤醒
	_notEmpty.notifyAll();
}

}//end of namespace wd


