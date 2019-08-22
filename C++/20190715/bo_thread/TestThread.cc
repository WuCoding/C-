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
				int number=::rand()%100;
				cout<<"sub Thread"<<pthread_self()
					<<":number="<<number<<endl;
				::sleep(1);
			}
		}
};

void task_process(int)
{
	::srand(::clock());

	int cnt=20;
	while(cnt--){
		int number=::rand()%100;
		cout<<"sub Thread"<<pthread_self()
			<<":number="<<number<<endl;
		::sleep(1);
	}
}

int main(void)
{

#if 1
	//因为类中的非static成员函数，自动含有一个this指针参数，不符合
	//回调函数的void()的函数类型，需要绑定一个对象，变为无参
	unique_ptr<wd::Thread> thread(
			new wd::Thread(
				std::bind(&Mytask::run,Mytask())
				)
			);
#endif

#if 0
	unique_ptr<wd::Thread> thread(
			new wd::Thread(
				std::bind(task_process,1)
				)
			);
#endif

	thread->start();

	thread->join();
	return 0;
}
