#include <iostream>
using std::cout;
using std::endl;
//         A
//        / \
//       B   C
//       \   /
//         D
//菱形继承，导致类D中存在两次类A的成员

class A
{
	public:
		//打印成员
		void print() const
		{
			cout<<"A::print() _a="<<_a<<endl;
		}
	private:
		//数据成员
		double _a;
};

class B
: public A
{
	private:
		//数据成员
		double _b;
};

class C
: public A
{
	private:
		//数据成员
		double _c;
};

class D
: public B
, public C
{
	//此时该类中包含了两次类A的非私有成员
	private:
		//数据成员
		double _d;
};

int main(void)
{
	//结果为8，数据成员类型为double占据8个字节
	cout<<"sizeof(A)="<<sizeof(A)<<endl;
	//结果为16，类A对象占据8个字节，自身double数据成员占据8个字节
	cout<<"sizeof(B)="<<sizeof(B)<<endl;
	//结果为16，类A对象占据8个字节，自身double数据成员占据8个字节
	cout<<"sizeof(C)="<<sizeof(C)<<endl;
	//结果为40，类B对象占据16个字节，类C对象占据16个字节，自身double数据成员占据8个字节
	cout<<"sizeof(D)="<<sizeof(D)<<endl;
	//派生类在创建自己的对象时，会同时创建一个自己的基类对象

	D d;
	//d.print();
	//该语句失败原因：
	//      >因为类D中包含两次类A中的print()成员函数，导致调用时，产生
	//      >存储布局的二义性
	

	//解决方案：
	//      >采用虚拟继承
	d.B::print();
	d.C::print();
	//这两次打印出的类A的数据对象_a的值都不一样
	//因为第一次打印的是d中的类B对象中的类A
	//对象，第二次打印的是d中的类C对象中的类A对
	//象，这两个类A对象不是同一个对象，各自有各
	//自的内存空间，当然数据成员的数值也不一样
	
	
	return 0;
}





























