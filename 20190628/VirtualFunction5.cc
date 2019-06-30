#include <iostream>
using std::cout;
using std::endl;

//构造函数和析构函数是特殊的成员函数，在其中访问虚函数时，
//C++采用静态联编，即在构造函数或析构函数内，即使是使用
//“this->虚函数名”的形式来调用，编译器仍将其解释为静态联
//编的“本类名::虚函数名”，即它们所调用的虚函数是自己类中定
//义的函数，如果自己的类中没有实现该函数，则调用的是基类中
//的虚函数。但绝对不会调用任何在派生类中重定义的虚函数


//基类
class Grandpa
{
	public:
		//构造函数
		Grandpa()
		{
			cout<<"Grandpa()"<<endl;
		}
		//虚函数
		virtual
		void func1()
		{
			cout<<"void Grandpa::func1()"<<endl;
		}

		virtual
		void func2()
		{
			cout<<"void Grandpa::func2()"<<endl;
		}

		//静态函数成员
		static void func3(Grandpa *pointer)
		{
			//func1();
			//该语句执行错误原因：
			//    >静态成员函数不能直接访问虚函数，因为其没有this指针
			//    >而虚函数的调用是要有this指针的
			
			//如果想在静态成员函数中调用虚函数，解决方案：
			//    >作为参数将指针传递给静态函数成员，通过参数指针
			//    >调用虚函数
			pointer->func1();
		}

		//析构函数
		~Grandpa()
		{
			cout<<"~Grandpa()"<<endl;
			func2();//静态联编，调用的是本类中的函数
		}
};

//派生类
class Parent
: public Grandpa //以public方式继承
{
	public:
		//构造函数
		Parent()
		{
			cout<<"Parent()"<<endl;
			func1(); //静态联编，不会表现动态多态特性调用的是本类中的func1()函数
		}

#if 1 
		//虚函数
		virtual
		void func1() 
		{
		
			cout<<"void Parent::func1()"<<endl;
		}

		virtual
		void func2()
		{
			cout<<"void Parent::func2()"<<endl;
		}
#endif
		//析构函数
		~Parent()
		{
			cout<<"~Parent()"<<endl;
			func2();//调用本类中的func2()函数
		}
};

//派生类
class Son
: public Parent  //以public方式继承
{
	public:
		//构造函数
		Son()
		: Parent() //调用基类构造函数
		{
			cout<<"Son()"<<endl;
			func1();//静态联编
		}

		//虚函数
		virtual
		void func1()
		{
			cout<<"void Son::func1()"<<endl;
		}

		virtual
		void func2()
		{
			cout<<"void Son::func2()"<<endl;
		}

		//析构函数
		~Son()
		{
			cout<<"~Son()"<<endl;
			func2();//相当于Son::func2();
		}
};

int main(void)
{

	Son son;

	return 0;
}









































