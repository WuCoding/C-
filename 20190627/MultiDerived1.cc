#include <iostream>
using std::cout;
using std::endl;

class A
{
	public:
		//构造函数
		A()
		{
			cout<<"A()"<<endl;
		}
		//打印函数
		void print() const
		{
			cout<<"A::print()"<<endl;
		}
	private:
		//数据成员
		int _a;
};

class B
{
	public:
		//构造函数
		B()
		{
			cout<<"B()"<<endl;
		}
		//打印函数
		void display() const  //注意：此处同样是打印函数，但不是用print命名，为了和
		{                     //A类中的打印成员函数区分开来 
			cout<<"B::display()"<<endl;
		}
	private:
		//数据成员
		int _b;
};

class C
{
	public:
		//构造函数
		C()
		{
			cout<<"C()"<<endl;
		}
		//打印函数
		void show() const  //注意：此处打印函数，用show命名，与class A和class B的打印函数
		{		   //区分开来
			cout<<"C::show()"<<endl;
		}

	private:
		//数据成员
		int _c;
};
#if 0
class D
: public A,B,C                 //注意：这里的目的为了同时将类A、B、C以public的形式继承，但事实是
{			       //除了A类以public形式继承，B、C类都是以private形式继承，因为默认
	public:		       //情况下是以private继承
		D()
		: A()//主动调用类A的构造函数
		, B()//主动调用类B的构造函数
		, C()//主动调用类C的构造函数
		{}
	private:
		//数据成员
		int _d;
};
#endif
class D
: public A //这种形式才是将A、B、C类都以public形式继承
, public B
, public C
{
	public:
		//构造函数
		D()
		: A()//主动调用类A的构造函数
		, B()//主动调用类B的构造函数
		, C()//主动调用类C的构造函数
		{}
	private:
		int _d;
};
int main(void)
{
	D d;
	d.print();//类A的成员函数
	d.display();//类B的成员函数
	d.show();//类C的成员函数

	return 0;
}
