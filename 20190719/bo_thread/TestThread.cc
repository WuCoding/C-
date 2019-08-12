#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Mytask
{

public:
	void run()
	{
		::srand(::clock());

		int cnt=20;
		while(cnt--){
			//获得一个随机数
			int number=::rand()%100;
			cout<<"sub Thread"<<pthread_self()//获得执行当前程序语句的线程号
				<<": number="<<number<<endl;
			::sleep(1);
		}
	}
};

void task_process(int)
{
	//子线程运行的地方
	::srand(::clock());

	//打印该线程的名称
	cout<<"cb:"<<wd::current_thread::threadName<<endl;

	int cnt=20;
	while(cnt--)
	{
		//获得一个随机数
		int number=::rand()%100;
		cout<<"sub Thread"<<pthread_self()//获得执行当前程序语句的线程号
			<<":number="<<number<<endl;
		::sleep(1);
	}
}


int main(void)
{
	//创建一个Thread的堆对象，传入回调函数，和线程名称
	//unique_ptr<wd::Thread> thread(new wd::Thread(std::bind(&Mytask::run,Mytask()),"1"));
	unique_ptr<wd::Thread> thread(new wd::Thread(std::bind(task_process,1),"1"));

	//执行该对象的start()函数，就是创建一个ThreadData的堆对象，传入回调函数和线程名称，
	//创建一个线程，将线程函数和ThreadData的堆对象传入，执行ThreadData的runInThread()函数
	//该函数实际就是执行回调函数
	thread->start();

	cout<<"main thread:"<<pthread_self()<<endl;
	cout<<"main thread获得thread对象的name"<<thread->getName()<<endl;//主线程

	thread->join();
	return 0;
}
	

