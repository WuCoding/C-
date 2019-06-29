#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//无参构造函数
		Base()
		: _base(0)
		{
			cout<<"Base()"<<endl;
		}
		
		//有参构造函数
		Base(double base)
		: _base(base)
		{
			cout<<"Base(double)"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"Base::_base="<<_base<<endl;
		}
	private:
		//数据成员
		double _base;
};

//派生类
class Derived
: public Base //以public的方式继承
{
	public:
		//当派生类没有显式定义构造函数，基类有显式定义构造函数，
		//要创建派生类对象时，在执行派生类构造函数的初始化表达式
		//时，调用基类的无参构造函数，完成基类部分（基类对象）的
		//初始化


		//无参构造函数
		Derived()
		{
			cout<<"Derived()"<<endl;
		}

		//打印函数
		void display() const
		{
			print(); //调用基类的打印函数
			cout<<", _derived="<<_derived<<endl;
		}

	private:
		double _derived;
};

int main(void)
{
	Derived derived;
	derived.display();

	return 0;
}
