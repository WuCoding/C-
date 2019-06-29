#include <iostream>
using std::cout;
using std::endl;

//错误的说法：
//    >创建派生类对象时，先调用基类构造函数，再调用派生类构造函数


//派生类对象创建时，先初始化基类部分，再初始化派生类部分
//先调用派生类构造函数，在执行派生类构造函数的过程中，
//再去调用基类的构造函数

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
			cout<<"Base::_base="<<_base;
		}

	private:
		//数据成员
		double _base;
};

//派生类
class Derived
: public Base //以public方式继承
{
	public:
		//当派生类有显式定义构造函数，基类没有显式定义构造函数
		//要创建派生类对象时，在执行派生类构造函数的初始化表达式
		//时，调用基类的无参构造函数，完成基类部分（基类对象）的
		//初始化


		//含一个参数的构造函数
		Derived(double derived)
		: Base(0)  //调用Base类的含参构造函数，完成基类部分的初始化
		, _derived(derived) 
		{
			cout<<"Derived(double)"<<endl;
		}

		//含两个参数的构造函数
		Derived(double base,double derived)
		: Base(base)
		, _derived(derived)
		{
			cout<<"Derived(double,double)"<<endl;
		}

		//打印函数
		void display() const
		{
			print(); //调用基类的打印函数
			cout<<",_derived="<<_derived<<endl;
		}

	private:
		//数据成员
		double _derived;
};

int main(void)
{
	Derived derived1(11.11,12.12);
	derived1.display();

	Derived derived2(11.11);
	derived2.display();

	return 0;
}




		








































