#include <iostream>
using std::cout;
using std::endl;

void func1(int x)
{
	//静态局部变量
	static int cnt=0;
	++cnt;
	cout<<"func1(int) x="<<x<<endl;
	cout<<"func1 has been called "<<cnt<<" times."<<endl;
}

struct Example
{
	//struct类内部成员默认访问权限为public
	
	//重载函数运算符，创建的对象为函数对象
	int operator()(int x,int y)
	{
		++cnt;
		cout<<"operator()(int,int) has been called "<<cnt<<" times"<<endl;
		return x+y;
	}

	int operator()(int x,int y,int z)
	{
		return x*y*z;
	}

	//数据成员
	int cnt=0;  //函数对象携带的状态=>闭包=>lambda表达式=>匿名函数
};

int main(void)
{
	Example example;
	int a=3,b=4,c=5;
	//重载了函数调用运算符的类创建的对象称为函数对象
	cout<<"example(a,b)="<<example(a,b)<<endl;
	//显示：
	//example(a,b)=operator()(int,int) has been called 1 times
	//7
	
	cout<<"example(a,b,c)="<<example(a,b,c)<<endl;
	//显示：
	//example(a,b,c)=60
	
	cout<<"example(a,b)="<<example(a,b)<<endl;
	//显示：
	//example(a,b)=operator()(int,int) has been called 2 times
	//7

	Example example2;
	cout<<"example2(a,b)="<<example2(a,b)<<endl;
	//显示：
	//example2(a,b)=operator()(int,int) has been called 1 times
	//7
	
	func1(a);
	//显示：
	//func1(int) x=3
	//func1 has been called 1 times.
	
	func1(a);
	//显示：
	//func1(int) x=3
	//func1 has been called 2 times.

	//lambda表达式
	auto f1=[](int number){
		cout<<"lambda expression"<<endl;
		cout<<"number="<<number<<endl;
	};

	f1(a);
	//显示：
	//lambda expression
	//number=3

	return 0;
}

