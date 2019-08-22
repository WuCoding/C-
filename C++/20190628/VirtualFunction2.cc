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

		//打印函数 虚函数 写有override关键字的函数为虚函数，且必须
		//有基类同名的虚函数来被覆盖掉，否则编译会报错，这样就可以
		//用来保证虚函数名和基类虚函数名相同，防止因为疏忽导致函数名
		//不一致，但编译和执行都不会报错的情况
		void display() const override//override覆盖
		{
			cout<<">>_child1="<<_child1<<endl;
		}
	private:
		//数据成员
		double _child1;
};

//不只是指针可以表现多态的特性
//引用也可以表现多态的特性
void display(Base & base)
{
	base.display();
}

int main(void)
{
	Base base(1);
	Child1 child1(11,12);
	display(base);
	display(child1);

	//通过对象名调用不会表现多态特性
	child1.display();
	//该语句不会用到对象中的vfptr指针来通过虚函数表来找到函数入口
	//而是直接到代码区，找到Child1::display()
	

	return 0;
}










































