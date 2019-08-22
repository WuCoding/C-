#include <iostream>
using std::cout;
using std::endl;

//编辑-->预处理（预编译）-->编译-->汇编-->链接-->可执行程序
//    -i                 -E            -S     as    -o
//怎么表示学会了一个知识点
//    完成任务-->讲出来-->别人还能听的懂

//宏定义与const的区别？（概念题是最容易丢分）
//1. 发生实际不一样：宏定义发生在预处理时，const关键字发生编译时
//2. 宏定义仅仅只做了字符串的替换，没有类型检查；const关键字有类型检查，
//可以提前发现错误
//3. const关键字更推荐使用；因为使用const关键字可以减小犯错误的概率

#define NUMBER 1024

void test0()
{
	cout<<"NUMBER="<<NUMBER<<endl;
}

void test1()
{
	const int number=1;	//常量必须要进行初始化
	cout<<">>number="<<number<<endl;

	number=10;
}

//常量指针  	指针常量

//数组指针  	指针数组
//int(*)[5]     int *[5]

//函数指针	指针函数
//int(*p)()	int *p()

void test2()
{
	int number=10;
	int number2=100;
	int *p1=&number;
	cout<<"*p1="<<*p1<<endl;
	cout<<"&p1="<<&p1<<endl;


