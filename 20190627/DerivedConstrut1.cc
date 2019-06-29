#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//构造函数
		Base()
		: _base(0)
		{
			cout<<"Base()"<<endl;
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
		//当派生类有显式定义构造函数，而基类没有显式定义构造函数
		//要创建派生类对象时，在执行派生类构造函数的初始化表达式
		//时，调用基类的无参构造函数，完成基类部分（也就是基类对象）
		//的初始化
		
		//派生类的构造函数
		Derived(double derived)
		: Base() //调用基类的无参构造函数
		, _derived(derived)
		{
			cout<<"Derived(double)"<<endl;
		}

		//打印函数
		void display() const
		{
			print();  //调用基类的打印函数
			cout<<", _derived="<<_derived<<endl;
		}

	private:
		//数据成员
		double _derived;
};

int main(void)
{
	Derived derived(11.11);
	derived.display();

	return 0;
}
