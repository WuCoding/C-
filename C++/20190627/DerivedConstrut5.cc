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

		//含参构造函数
		Base(double base)
		: _base(base)
		{
			cout<<"Base::_base="<<_base<<endl;
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
: public Base //以public方式继承
{
	public:
		//含一个参数的构造函数
		Derived(double derived)
		: Base(0)
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
			print();  //调用基类的打印函数
			cout<<",_derived="<<_derived<<endl;
		}

		//析构函数
		~Derived()
		{
			cout<<"~Derived()"<<endl;
		}

	private:
		//数据成员
		double _derived;
};

class GrandSon
: public Derived //以public方式继承Derived类
{
	public:
		//构造函数
		GrandSon(double base,double derived,double grandson)
		: Derived(base,derived) //调用Derived类的构造函数
		, _grandson(grandson)
		{
			cout<<"GrandSon(double,double,double)"<<endl;
		}

		//析构函数
		~GrandSon()
		{
			cout<<"~GrandSon()"<<endl;
		}
	private:
		//数据成员
		double _grandson;
};

int main(void)
{
	GrandSon grandson(11.11,12.12,13.13);
	grandson.display();

	//构造GrandSon类的对象时，先初始化Base类，再初始化Derived类，再初始化GrandSon类
	//销毁GrandSon类的对象时，刚好相反，先销毁GrandSon类，再销毁Derived类，再销毁Base类
	return 0;
}





