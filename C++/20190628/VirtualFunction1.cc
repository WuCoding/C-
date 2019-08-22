#include <iostream>
using std::cout;
using std::endl;

//构造函数不能被声明为虚函数，为什么？
//答：  
//    >这里就涉及到了虚函数机制的触发条件，要触发虚函数机制，首先要有一个对象，
//    >该对象中存储有一个vfptr指针，该指针指向一个虚函数表，再通过该虚函数表
//    >获得函数的入口地址，构造函数执行时，对象还没创建出来，vfptr指针也还不
//    >存在，所以无法触发虚函数机制，所以构造函数不能设为虚函数

class Base
{
	public:
		//构造函数
		//virtual
		Base(double base)
		: _base(base)
		{
			cout<<"Base()"<<endl;
		}

		//打印函数 虚函数
		virtual
		void display() const
		{
			cout<<">>base="<<_base<<endl;
		}
	private:
		//数据成员
		double _base;
};

//派生类
class Child1
: public Base //以public方式继承
{
	public:
		//构造函数
		Child1(double base,double child)
		: Base(base)  //调用基类的构造函数
		, _child1(child)
		{
			cout<<"Child(double,double)"<<endl;
		}
		
		//打印函数 虚函数
		void display() const
		{
			cout<<">>_child1="<<_child1<<endl;
		}

	private:
		//数据成员
		double _child1;
};

class Child2
: public Base //以public方式继承
{
	public:
		//构造函数
		Child2(double base,double child)
		: Base(base) //调用基类构造函数
		, _child2(child)
		{
			cout<<"Child(double,double)"<<endl;
		}

		//打印函数 虚函数
		void display() const
		{
			cout<<">>_child2="<<_child2<<endl;
		}
	private:
		//数据成员
		double _child2;
};

void display(Base * pbase)
{
	pbase->display();
}

int main(void)
{
	cout<<"sizeof(Base)="<<sizeof(Base)<<endl;
	cout<<"sizeof(Child1)="<<sizeof(Child1)<<endl;
	cout<<"sizeof(Child2)="<<sizeof(Child2)<<endl;

	Base base(1);
	Child1 child1(11,12);
	Child2 child2(21,22);

	display(&base);
	display(&child1);
	display(&child2);

	Child1 *p=&child1;
	p->display();

	return 0;
}

































