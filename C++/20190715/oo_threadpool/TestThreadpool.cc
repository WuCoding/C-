#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class Mytask
: public Task
{
public:
	void process()
	{
		::srand(::time(nullptr));
		int number=::rand()%100;
		cout<<">>sub Thread"<<pthread_self()
			<<"Mytask:number="<<number<<endl;
		::sleep(1);
	}

	~Mytask()
	{
		cout<<"Mytask()"<<endl;
	}
};

int main(void)
{
	unique_ptr<Task> task(new Mytask());//基类指针指向派生类对象
	Threadpool threadpool;
	threadpool.start();

	int cnt=20;
	while(cnt--){
		//将任务加入到任务队列中
		threadpool.addTask(task.get());
		//从任务队列中取任务执行就是执行Task*指针所指向的对象的process()函数
		cout<<"main thread"<<pthread_self()
			<<": cnt="<<cnt<<endl;
	}

	threadpool.stop();

	return 0;
}


