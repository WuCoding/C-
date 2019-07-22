#include "Thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

//派生类
class MyThread
: public wd::Thread
{
	//该派生类只有重写了run()这个纯虚函数
	void run()
	{
		::srand(::clock());

		int cnt=20;
		while(cnt--){
			int number=::rand()%100;
			cout<<"sub Thread"<<pthread_self()//获得该线程id
				<<":number="<<number<<endl;
			::sleep(1);
		}
	}
};

int main(void)
{
	unique_ptr<wd::Thread> thread(new MyThread());
	thread->start();

	thread->join();

	MyThread thread1;
	MyThread thread2=thread1;
	return 0;
}
