#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//构造函数
		Base(double base)
		: _base(base)
		{
			cout<<"Base()"<<endl;
		}

		//在成员函数中访问，一样体现出动态多态特性
		void func1()
		{
			display();
			//通过基类指针访问func1()成员函数时，实际
			//在调用display()虚函数时，依然体现出动态
			//多态特性。
			//原因：
			//    >该语句实际为this->display();
			//    >通过this指针来调用display()
			//    >符合虚函数触发机制的条件    
		}

		void func2()
		{
			//该语句由于被类名限制，所以无法触发动态多态特性
			Base::display();
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
		: Base(base)
		, _child1(child)
		{
			cout<<"Child(double,double)"<<endl;
		}

		//打印函数 虚函数
		virtual
		void display() const
		{
			cout<<">>_child1="<<_child1<<endl;
		}

	private:
		//数据成员
		double _child1;
};

int main(void)
{
	Base base(1);
	Child1 child1(11,12);

	//一个基类指针，指向一个基类对象
	Base *pbase=&base;
	//调用基类的display方法
	pbase->func1();
	//调用基类的display方法
	pbase->func2();

	//一个基类指针，指向一个派生类对象
	pbase=&child1;
	//调用派生类的display方法
	pbase->func1();
	//调用基类的display方法，因为func2()中display()方法已经被类名限定了，无法体现动态
	//多态特性
	pbase->func2();

	return 0;
}






