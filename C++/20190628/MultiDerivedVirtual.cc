#include <iostream>
using std::cout;
using std::endl;

class A
{
	public:
		virtual
		void a()
		{
			cout<<"A::a()"<<endl;
		}

		virtual
		void b()
		{
			cout<<"A::b()"<<endl;
		}

		virtual
		void c()
		{
			cout<<"A::c()"<<endl;
		}
};//A类虚函数：a()、b()、c()

class B
{
	public:
		virtual 
		void a()
		{
			cout<<"B::a()"<<endl;
		}

		virtual
		void b()
		{
			cout<<"B::b()"<<endl;
		}

		void c()
		{
			cout<<"B::c()"<<endl;
		}

		void d()
		{
			cout<<"B::d()"<<endl;
		}
};//B类虚函数：a()、b()  B类普通成员函数：c()、d()

class C
: public A  //以public方式继承类A和类B
, public B
{
	public:
		virtual 
		void a()
		{
			cout<<"C::a()"<<endl;
		}

		void c()
		{
			cout<<"C::c()"<<endl;
		}

		void d()
		{
			cout<<"C::d()"<<endl;
		}
};

int main(void)
{
	C c;
	//基类A指针指向派生类对象
	A *pa=&c;
	//用该A基类指针进行a()、b()、c()函数的调用
	pa->a();  //C::a()
	pa->b();  //A::b()
	pa->c();  //C::c()

	cout<<endl;

	//基类B指针指向派生类对象
	B *pb=&c;
	//用该B基类指针进行a()、b()、c()、d()函数调用
	pb->a();  //C::a()
	pb->b();  //B::b()
	pb->c();  //B::c()
	pb->d();  //B::d()

	cout<<endl;
#if 1
	//派生类指针指向派生类对象
	C *pc=&c;
	pc->a();  //C::a()
	//pc->b(); 该语句造成二义性 类A中有b()函数，类B中也有b()函数
	pc->c();  //C::c()
	pc->d();  //C::d()
#endif

	//打印结果为：
	//pa等于pc不等于pb
	cout<<"pa="<<pa<<endl
		<<"pb="<<pb<<endl
		<<"pc="<<pc<<endl;
}
