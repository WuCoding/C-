#include <iostream>
using std::cout;
using std::endl;

class A
{
	public:
		//打印函数
		void print() const
		{
			cout<<"A::print()"<<endl;
		}
};

class B
{
	public:
		//打印函数
		void print() const //注意：此处的打印函数与类A的打印函数重名
		{
			cout<<"B::print()"<<endl;
		}
};

class C
{
	public:
		//打印函数
		void print() const//注意：此处的打印函数与类A类B的打印函数都重名
		{
			cout<<"C::print()"<<endl;
		}
};

class D
: public A
, public B
, public C
{};

int main(void)
{
	D d;
	//d.print();
	//该语句执行失败原因：
	//      >因为print()函数在类A、B、C中都有定义，导致系统不知要调用哪个
	//      >函数，造成成员名访问冲突的二义性
	
	//解决方案：
	//      >直接使用作用域限定符
	d.A::print();
	d.B::print();
	d.C::print();

	return 0;

}
