#include "MutexLock.h"
#include "Condition.h"

#include <iostream>
using std::cout;
using std::endl;
//测试自己写的MutexLock类和Condition类是否可以正常使用
//用卖票例子测试

int tickets=1000;
//flag为true时线程1卖票，flag为false时线程2卖票
bool flag=true;
//创建锁的对象
wd::MutexLock mutex;
//wd::MutexLock mutex2(mutex); 错误，锁是无法复制的，所以在锁的类内部已经将复制构造函数和赋值运算符重载函数置为delete
//创建条件变量的对象
wd::Condition cond(mutex);

//1号卖票线程函数
void * threadfunc1(void * arg)
{
	//1号窗口，当flag为true时，卖票
	int cnt=100;//设定他卖100张票
	while(cnt--)
	{
		//先上锁，用锁的保护类对象，创建对象时自动上锁，对象消亡时自动解锁，防止因为异常行为，直接退出，导致死锁
		wd::MutexLockGuard autolock(mutex);
		//flag==false时，该线程睡在条件变量上
		if(!flag){
			cond.wait();
		}
		//此时flag已经成为了true
		//进行卖票行为
		--tickets;
		cout<<">>1号窗口卖票之后，还剩余"<<tickets<<"票"<<endl;
		//将标志位置为false
		flag=false;
		//唤醒一个睡在条件变量上的线程
		cond.notify();
	}
	return nullptr;
}
//2号卖票线程函数
void * threadfunc2(void * arg)
{
	//2号窗口，当flag为false时，卖票
	int cnt=100;//设定他卖100张票
	while(cnt--)
	{
		//先上锁，用锁的保护类对象，创建对象时自动上锁，对象消亡时自动解锁，防止因为异常行为，直接退出，导致死锁
		wd::MutexLockGuard autolock(mutex);
		//flag==true时，该线程睡在条件变量上
		if(flag){
			cond.wait();//睡在该条件变量上
		}
		//此时说明flag已经成为false
		//进行卖票行为
		--tickets;
		cout<<">> 2号窗口卖票之后，还剩余"<<tickets<<"票"<<endl;
		//将flag置为true
		flag=true;
		//将睡在该条件变量的线程唤醒一个
		cond.notify();
	}
	return nullptr;
}

int main(void)
{
	pthread_t pthid1,pthid2;

	//创建两个线程
	pthread_create(&pthid1,nullptr,threadfunc1,nullptr);
	pthread_create(&pthid2,nullptr,threadfunc2,nullptr);

	//等待回收两个线程
	pthread_join(pthid1,nullptr);
	pthread_join(pthid2,nullptr);

	return 0;
}
	


