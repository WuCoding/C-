#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class Mytask
{
public:
	void process()
	{
		::srand(::time(nullptr));
		int number=::rand()%100;
		cout<<">> sub Thread"<<pthread_self()
			<<"Mytask:number="<<number<<endl;
		::sleep(1);
	}

	~Mytask()
	{
		cout<<"~Mytask()"<<endl;
	}
};

int main(void)
{
	Threadpool threadpool;
	//创建出了全部子线程
	threadpool.start();

	Mytask task;

	int cnt=20;
	while(cnt--){
		//向任务队列中加任务，说明此时主线程是生产者，子线程是消费者
		//threadpool.addTask(std::bind(&Mytask::process,Mytask()));
		threadpool.addTask(std::bind(&Mytask::process,&task));
		cout<<"main thread"<<pthread_self()
			<<": cnt="<<cnt<<endl;
	}

	//回收子线程
	threadpool.stop();

	return 0;
}


