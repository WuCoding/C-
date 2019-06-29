#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//构造函数
		Base(int x)
		: _x(x)
		{
			cout<<"Base(int)"<<endl;
		}

		//打印函数
		void display() const
		{
			cout<<"Base::_x="<<_x<<endl;
		}

	private:
		//数据成员
		double _x;
};

//派生类
class Derived
: public Base //public方式继承
{
	public:
		//构造函数
		Derived(int x,int y)
		: Base(x) //主动调用基类的构造函数来初始化基类部分
		, _y(y)
		{
			cout<<"Derived(int,int)"<<endl;
		}

		//打印函数
		void display() const
		{
			cout<<"Derived::_y="<<_y<<endl;
		}
	private:
		//数据成员
		double _y;
};

//派生类能够适应基类（派生类的功能要多于基类）
//    >可以把一个派生类对象赋值给基类对象
//    >可以把一个基类指针指向派生类对象
//    >可以把一个基类引用绑定到派生类对象

int main(void)
{
	//基类对象
	Base base(10);
	base.display();
	//派生类对象
	Derived derived(11,20);

	//derived=base;
	//这条语句错误原因：
	//     >此条语句实际执行的是Derived & operator=(const Derived & rhs)
	//     >const Derived & rhs=base; 将基类对象赋给派生类对象是错误的
	
	base=derived;
	//这条语句实际执行的是Base & operator=(const Base & rhs)
	//const Base & rhs=derived; 将派生类对象赋给基类对象是可行的
	
	base.display();

	//将基类指针指向派生类的对象，是可行的
	Base * pbase=&derived;
	pbase->display();

	//Derived * pderived=&base;
	//这条语句错误原因：
	//      >此语句将基类的对象地址赋给了派生类的指针，这是错误的
	//      >会造成访问越界

	//因为pbase虽然是个基类指针，但他指向的是一个派生类的对象，所以他强转为
	//基类指针，即向下转型是OK的
	Derived * pderived=(Derived *)pbase;
	pderived->display();

	Base * pbase2=&base;
	Derived * pderived2=(Derived *)pbase2;
	//该语句的向下转型是有问题的，原因：
	//      >pbase2本身是基类指针，且指向的是基类的对象，将他强转为派生类指针
	//      >相当于让一个派生类的指针指向一个基类对象，会造成访问越界，产生运
	//      >行时的错误
	
	return 0;
}

	








































