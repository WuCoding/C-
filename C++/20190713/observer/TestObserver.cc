#include "Subject.h"
#include "Observer.h"

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

void test0()
{
	unique_ptr<Observer> baby1(new Baby("豆豆"));
	unique_ptr<Observer> baby2(new Baby("小米"));

	unique_ptr<Observer> nurse1(new Nurse("小丽"));
	unique_ptr<Observer> nurse2(new Nurse("小红"));

	Ring ring;
	//将两个宝宝和两个护士加入都观察者队列
	ring.attach(baby1.get());
	ring.attach(baby2.get());
	ring.attach(nurse1.get());
	ring.attach(nurse2.get());

	Guest guest("熊大");
	//客人开始按铃
	guest.knock(ring);
	cout<<"------"<<endl;

	//将护士2从观察者队列中删除
	ring.detach(nurse2.get());

	//再次开始按铃
	guest.knock(ring);
}

int main(void)
{
	test0();
	return 0;
}



