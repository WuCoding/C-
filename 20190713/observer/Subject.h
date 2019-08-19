#pragma once

#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;

class Observer;//不需要知道类内部的情况，使用前向声明

using Status=bool;

class Subject
{
public:
	//纯虚函数
	virtual void attach(Observer *ob)=0;
	virtual void detach(Observer *ob)=0;
	virtual void notify()=0;
	//virtual Status getStatus()=0;
	//virtual void setStatus(Status status)=0;
	
	virtual ~Subject()
	{}
};

class Ring
: public Subject
{
public:
	Ring()
	: _isRing(false)
	{}

	void alarm();
	void attach(Observer *ob) override;
	void detach(Observer *ob) override;
	void notify() override;
private:
	bool _isRing;
	list<Observer*> _oblist;
	
	//业务比较复杂的情况下，可以对观察者进行分类
	//list<Observer*> _goldenList;
	//list<Observer*> _whiteGoldenList;
};
