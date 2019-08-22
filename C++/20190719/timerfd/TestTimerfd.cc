#include "TimerThread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

//输出一个随机数
void getNumber()
{
	::srand(::time(nullptr));
	int number=::rand()%100;

	cout<<">> sub thread:timerfd get a number="<<number<<endl;
}

int main(void)
{
	wd::TimerThread timer(3,6,getNumber);

	timer.start();

	cout<<"main thread"<<endl;
	::sleep(20);

	timer.stop();

	return 0;
}

