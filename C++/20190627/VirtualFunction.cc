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

		//虚函数
		virtual void display() const
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
		: Base(base)  //调用基类的构造函数来初始化派生类中的基类部分
		, _child1(child)
		{
			cout<<"Child(double,double)"<<endl;
		}

		//对于派生类而言，当派生类重定义基类的虚函数时，
		//即使在其前面没有加上virtual，它也是虚函数
#if 1
		//virtual void display(int idx) const 这里函数参数类型改变，由无参改为有参
		//此时他就相当于一个新定义的一个虚函数，而不是和基类同名的虚函数了
		
		//虽然该函数并未在函数名前加virtual关键字，但他依然是个虚函数
		void display() const
		{
			cout<<">> _child1="<<_child1<<endl;
		}
#endif
	private:
		//数据成员
		double _child1;
};

//派生类
class Child2
: public Base  //以public方式继承
{
	public:
		//构造函数
		Child2(double base,double child)
		: Base(base)
		, _child2(child)
		{
			cout<<"Child(double,double)"<<endl;
		}

		//打印函数，也是个虚函数
		void display() const
		{
			cout<<">> _child2="<<_child2<<endl;
		}

	private:
		//数据成员
		double _child2;
};

//派生类重定义基类虚函数时，必须与基类的虚函数完全保持一致

//虚函数的实现原理：
//    >当类中定义了虚函数时，在其对象的存储布局之中会多一个虚函数指针
//    >该虚函数指针指向了一张虚函数表，虚函数表中存放的就是虚函数的入
//    >口地址。

//如何激活动态多态的特性（虚函数机制被激活的条件）？
//1. 基类要定义虚函数，派生类要重定义（覆盖）虚函数
//2. 创建派生类对象
//3. 用基类指针指向派生类对象
//4. 用基类指针调用虚函数

//动态多态：在运行时才会看到效果
//当发生动态多态时，调用的函数与指针本身的类型无关，只与其所指的对象有关

void display(Base * pbase)
{
	pbase->display();
}

int main(void)
{
	//结果为16，虚函数表指针vfptr占8字节，double类型的数据成员占8字节
	cout<<"sizeof(Base)="<<sizeof(Base)<<endl;
	//结果为24，基类Base部分占16字节（虚函数表指针占8字节，double类型数据成员占8字节），
	//派生类的数据成员double类型占8字节
	cout<<"sizeof(Child1)="<<sizeof(Child1)<<endl;
	//结果为24，基类Base部分占16字节（虚函数表指针占8字节，double类型数据成员占8字节），
	//派生类的数据成员double类型占8字节
	cout<<"sizeof(Child2)="<<sizeof(Child2)<<endl;

	Base base(1);
	Child1 child1(11,12);
	Child2 child2(21,22);

	display(&base);//调用Base类的display()成员
	display(&child1);//调用Child1类的display()成员
	display(&child2);//调用Child2类的display()成员

	Child1 * p=&child1;
	p->display();
	//调用的是Child1类的display()成员，这里就不再通过虚函数表来获取函数入口地址，
	//而是直接得到函数入口地址，进行调用，与普通成员函数无异。

	return 0;
}


