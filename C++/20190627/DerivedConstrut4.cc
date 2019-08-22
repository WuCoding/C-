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
			cout<<"Base::_base="<<_base;
		}

		//析构函数
		~Base()
		{
			cout<<"~Base()"<<endl;
		}

	private:
		//数据成员
		double _base;
};

//派生类
class Derived
: public Base  //以public的方式来继承
{
	public:
		//含两个参数的构造函数
		Derived(double derived,double base)
		: Base(0)  //对于基类部分的初始化，是通过类名调用构造函数
		, _derived(derived)
		, _base(base)  //对于对象成员，是通过对象名调用构造函数
		{
			cout<<"Derived(double)"<<endl;
		}

		//含三个参数的构造函数
		Derived(double base,double derived,double base1)
		: Base(base)
		, _derived(derived)
		, _base(base)
		{
			cout<<"Derived(double,double)"<<endl;
		}

		//打印函数
		void display() const
		{
			print();  //调用基类的打印函数
			cout<<",_derived="<<_derived<<endl;
		}

		//析构函数
		~Derived()
		{
			cout<<"~Derived()"<<endl;
		}
	private:
		double _derived;
		//对象成员
		Base _base;
};

int main(void)
{
	Derived derived1(11.11,12.12,33.33);
	derived1.display();

	Derived derived2(11.11,22.22);
	derived2.display();

	//构造派生类对象时，先初始化基类部分，再初始化派生类的数据成员
	//销毁派生类对象时，先销毁派生类的数据成员，再销毁基类部分

	return 0;
}

















































































