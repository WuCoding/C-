#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

//默认参数/缺省参数
//一旦某个参数被设置了默认值，后面的所有的参数都要设置默认值
//默认参数的设置只能从右往左进行
int add(int x=0,int y=0)
{
	return x+y;
}
int add(int x,int y,int z)
{
	return x+y+z;
}

int main(void)
{
	int a=3,b=4,c=5;
	cout<<"add(a)="<<add(a)<<endl;
	cout<<"add(a,b)="<<add(a,b)<<endl;
	cout<<"add(a,b,c)="<<add(a,b,c)<<endl;

	return 0;
}
