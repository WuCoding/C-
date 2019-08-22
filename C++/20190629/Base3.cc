#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//构造函数
		Base()
		{}

		//打印函数 虚函数
		virtual void display() const
		{
			cout<<"Base::display()"<<endl;
		}
	private:
		//数据成员
		int _base;
};

//派生类
class Derived
: public Base //以public方式继承
{
	public:
		//构造函数
		Derived()
		: Base() //调用基类的构造函数
		{}

		//打印函数 虚函数
		//在虚函数的末尾使用final关键字，表示该虚函数不能再被覆盖
		virtual
		void display() const final
		{
			cout<<"Derived::display()"<<endl;
		}
};

//派生类
class Son
: public Derived //以public方式继承
{
	public:
		//打印函数 虚函数
		virtual void display() const  //由于基类中同名虚函数已经加了final关键字，所以
		{                             //将会编译出错
			cout<<"Son::display()"<<endl;
		}
};

int main(void)
{
	Derived derived;
}

