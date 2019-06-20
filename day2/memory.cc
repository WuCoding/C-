#include <stdio.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

//全局静态区，全局变量如果没有显示进行初始化，系统也会设置默认值
int a=1;
char *p1;

int test0(void)
{
	int b=2;//栈空间
	const char *p2="hello,world";//文字常量区
	char str[]="hello,world";//栈空间
	//str指针是常量不能被改变值，如 str=0x123439ac8是错误的
	
	char *p3;//野指针
	p3=new char[20]();//堆空间
	strcpy(p3,"hello,world");

	static int c=100;//局部静态变量，位于数据段 全局/静态区
	++c;

	printf("sizeof(str)=%lu\n",sizeof(str));
	printf("sizeof(p2)=%lu\n",strlen(p2));

	printf("&a=%p\n",&a);
	printf("&b=%p\n",&b);	
	printf("p1=%p\n",p1);	
	printf("&p1=%p\n",&p1);
	printf("p2=%p\n",p2);
	printf("&p2=%p\n",&p2);


	printf("str=%p\n",str);
	printf("p3=%p\n",p3);
	printf("&p3=%p\n",&p3);
	printf("&c=%p\n",&c);
	printf("address(hello,world)=%p\n","hello,world");
	printf("address(test0)=%p\n",&test0);//程序代码区
	return 0;
}
int main(void)
{
	test0();
	return 0;
}

