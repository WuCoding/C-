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

		//打印函数 含参虚函数
		virtual
		void display(int idx=0) const
		{
			cout<<">>base="<<_base<<",idx="<<idx<<endl;
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
		: Base(base) //调用基类的构造函数
		, _child1(child)
		{
			cout<<"Child(double,double)"<<endl;
		}

		//打印函数 含参虚函数
		virtual
		void display(int idx=1) const
		{
			cout<<">>_child1="<<_child1<<",idx="<<idx<<endl;
		}
	private:
		//数据成员
		double _child1;
};

int main(void)
{
	//易错题

	Base base(1);
	Child1 child1(11,12);

	//如果基类和派生类的虚函数都设置了默认值，且默认值还各不相同，
	//当通过指针或者引用调用虚函数时，默认值的使用只跟指针类型有关
	
	
	//基类指针指向基类对象的情况
	Base *pbase=&base;
	pbase->display();//该语句调用基类的打印函数，且用的虚函数的默认值为
	                 //基类虚函数的默认值

	//基类指针指向派生类对象
	pbase=&child1;
	pbase->display();//该语句调用派生类的打印函数，但用的函数默认值为基类
	                 //虚函数的默认值（是不是很神奇！！）函数默认值只与指针
			 //类型有关

	//派生类的指针指向派生类的对象
	Child1 * pchild1=&child1;
	pchild1->display();//该语句调用派生类的打印函数，用的函数默认值为派生类
	                   //打印函数的默认值

	return 0;
}



