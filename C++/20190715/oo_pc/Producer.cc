#include "Producer.h"
#include "TaskQueue.h"  //在Producer类的实现中才加入TaskQueue类型的头文件

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//子线程执行的操作函数
void Producer::run()
{
	::srand(::time(nullptr));
	int cnt=10;
	while(cnt--)
	{
		int number=::rand % 100;
		//将任务放入任务队列中
		_que.push(number);
		cout<<"cnt="<<cnt<<"producer thread"<<pthread_self()
			<<": produce a number="<<number<<endl;
	}

}

}//end of namespace wd


