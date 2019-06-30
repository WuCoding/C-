#include <iostream>
using std::cout;
using std::endl;

//抽象类的第二种形式：定义了protected构造函数的类也成为抽象类
//基类 抽象类
class Base
{
	protected:
		//protected型的构造函数
		Base(double base)
		: _base(base)
		{
			cout<<"Base(double)"<<endl;
		}

		//protected型的打印函数
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
: public Base //以public方式继承
{
	public:
		//构造函数
		Derived(double base,double derived)
		: Base(base)           //主动调用Base类的构造函数，该函数在Base类中为protected型成员
		, _derived(derived)    //在派生类的内部可见
		{
			cout<<"Derived(double,double)"<<endl;
		}

		//打印函数
		void display() const
		{
			print(); //该函数在基类中为protected型成员，在派生类内部可被访问
			cout<<"Derived::_derived="<<_derived<<endl;
		}
	private:
		//数据成员
		double _derived;
};

int main(void)
{
	//Base base(1.11);
	//该语句执行失败原因：
	//    >因为Base类的构造函数为protected型成员，
	//    >对外界来说是不可见的，所以创建该类对象
	//    >失败。

	Derived derived(11.11,12.12);
	derived.display();

	return 0;
}
