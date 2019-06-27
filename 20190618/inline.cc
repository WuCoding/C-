#include <iostream>
using std::cout;
using std::endl;
//带参数的宏定义
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MULTIPY(x,y) ((x)*(y))
//使用带参数的宏定义
int test0(void)
{
	int a=3,b=4,c=5;
	printf("MAX(a,b)=%d\n",MAX(a,b));
	cout<<"MAX(a,b)="<<MAX(a,b)<<endl;
	printf("(a+b)*c=%d\n",MULTIPY(a+b,c));
	return 0;
}

//inline函数功能与带参数的宏定义效果一样
//尽量用inline函数替换带参数的宏定义
inline int max(int x,int y)
{
	return x>y?x:y;
}
inline int multiply(int x,int y)
{
	return x*y;
}

//使用inline函数
void test1()
{
	int a=3,b=4,c=5;
	cout<<"inline max(a,b)="<<max(a,b)<<endl;
	cout<<"inline multiply (a+b)*c="<<multiply(a+b,c)<<endl;
}

int main()
{
	test0();
	test1();
	return 0;
}
