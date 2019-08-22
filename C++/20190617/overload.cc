#include <stdio.h>

#include <iostream>
using std::cout;
using std::endl;

//C++语言支持函数重载
//实现原理：名字改编（name mangling）
//具体步骤：当函数名称相同时，会根据函数参数的类型、个数、顺序进行改编

int add(int x,int y)
{
	printf("int add(int,int)=");
	return x+y;
}
int add(int x,int y,int z)
{
	printf("int add(int,int,int)=");
	return x+y+z;
}

double add(double x,double y)
{
	printf("double add(double,double)=");
	return x+y;
}

double add(int x,double y)
{
	printf("double add(int,double)=");
	return x+y;
}

double add(double x,int y)
{
	printf("double add(double,int)=");
	return x+y;
}

int main(void)
{
	int a=3,b=4,c=5;
	double d1=1.1,d2=2.2;

	cout<<"add(int a,int b)调用"<<add(a,b)<<endl;
	cout<<"add(int a,int b,int c)调用"<<add(a,b,c)<<endl;
	cout<<"add(double d1,double d2)调用"<<add(d1,d2)<<endl;
	cout<<"add(int a,double d1)调用"<<add(a,d1)<<endl;
	cout<<"add(double d2,int b)调用"<<add(d2,b)<<endl;

	return 0;
}
