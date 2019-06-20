#include <iostream>
using std::cout;
using std::endl;

void test0()
{
	int number=1;
	int &ref=number;
	cout<<"ref="<<ref<<endl;
	cout<<"number="<<number<<endl;
	//对引用进行赋值,被引用对象也发生改变
	ref=10;
	cout<<">>修改引用之后："<<endl;
	cout<<"ref="<<ref<<endl;
	cout<<"number="<<number<<endl;
	//打印引用的地址和被引用对象的地址
	cout<<"&ref="<<&ref<<endl
		<<"&number="<<&number<<endl;
}
//引用作为函数参数
void swap(int &x,int &y)
{
	int temp=x;
	x=y;
	y=temp;
}

void test1()
{
	int a=3,b=4;
	cout<<"a="<<a<<",b="<<b<<endl;
	swap(a,b);
	cout<<"a="<<a<<",b="<<b<<endl;
}

//引用作为返回值
int array[5]={1,2,3,4,5};

int& getNumber(int idx)
{
	return array[idx];
}
//不能返回一个局部变量的引用
/*
int& func2()
{
	int number=5;
	return number;//在该函数执行结束后该局部变量生命周期已经结束
}
*/
//对堆空间的变量的引用
int& func3()
{
	int *p3=new int(100);
	return *p3;
}
void test2()
{
	int idx=0;
	cout<<"array[idx]="<<getNumber(idx)<<endl;
	
	getNumber(idx)=10;//左值：就是可以取地址，右值（临时变量）：不可以取地址
	cout<<"array[idx]="<<getNumber(idx)<<endl;

	int &ref2=func3();
	cout<<"ref2="<<ref2<<endl;
	delete &ref2;
}
int main(void)
{
	test2();
	return 0;
}


































