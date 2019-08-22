#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
#include <functional>
using std::queue;

namespace wd
{

using Task=std::function<void()>;
//任务其实就是让线程执行的线程函数
using ElemType=Task;

class TaskQueue
{

public:
	//构造函数，传递任务队列大小
	TaskQueue(size_t sz);

	//判断任务队列是否为空
	bool empty() const;
	//判断任务队列是否已满
	bool full() const;
	//将任务加入到任务队列中
	void push(ElemType elem);
	//将任务从任务队列中拿出，返回值为拿出的任务
	ElemType pop();

	void wakeup();

private:
	//数据成员
	size_t _sz;//任务队列长度
	queue<ElemType> _que;//任务队列
	MutexLock _mutex;//互斥锁
	Condition _notEmpty;//不空的条件变量
	Condition _notFull;//不满的条件变量
	bool _flag;
};

}//end of namespace wd

#endif
