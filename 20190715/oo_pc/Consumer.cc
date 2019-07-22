#include "Consumer.h"
#include "TaskQueue.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//消费者线程类型执行的具体操作函数实现
void Consumer::run()
{
	int cnt=20;
	while(cnt--)
	{
		int number=_que.pop();
		cout<<"consumer thread"<<pthread_self()<<"cnt="<<cnt
			<<": consume a number="<<number<<endl;

		::sleep(1);
	}
}
}//end of namespace wd
