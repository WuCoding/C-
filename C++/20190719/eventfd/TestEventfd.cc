#include "EventThread.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::cout;
using std::endl;

void getNumber()
{
	::srand(::time(nullptr));
	//获得一个100之内的随机数
	int number=::rand()%100;
	cout<<">> sub thread: get a number="<<number<<endl;
}
int main(void)
{
	//向eventfd对象传入回调函数
	wd::EventThread eventfd(getNumber);
	//实际进行的是调用线程类型Thread的start()函数，创建子线程，并传入Eventfd类的start()
	//函数和Eventfd指针，作为子线程的执行的线程函数，实际子线程执行的是Eventfd的start()
	//函数，该函数执行对eventfd可读事件的监控，如果可读则执行该Eventfd对象的回调函数成
	//员_cb
	eventfd.start();
	int cnt=10;
	while(cnt--){
		//向eventfd对象中的计数器counter增加整数
		eventfd.wakeup();
		cout<<"main thread notify sub thread..."<<endl;
		::sleep(1);
	}

	cout<<"main thread"<<endl;
	eventfd.stop();

	return 0;
}
