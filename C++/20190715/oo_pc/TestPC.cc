#include "TaskQueue.h"
#include "Producer.h"
#include "Consumer.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using namespace wd;

int main(void)
{
	//创建任务队列，容量为10
	TaskQueue taskque(10);

	//创建2个生产者线程，2个消费者线程，用基类指针指向派生类对象
	unique_ptr<Thread> producer1(new Producer(taskque));
	unique_ptr<Thread> producer2(new Producer(taskque));
	unique_ptr<Thread> consumer1(new Consumer(taskque));
	unique_ptr<Thread> consumer2(new Consumer(taskque));

	//启动线程
	producer1->start();
	producer2->start();
	consumer1->start();
	consumer2->start();

	//回收线程
	producer1->join();
	producer2->join();
	consumer1->join();
	consumer2->join();

	return 0;
}
