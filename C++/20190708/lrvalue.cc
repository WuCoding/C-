#include <iostream>
#include <string>
using std::cout;
using std::endl;

using std::string;
int main(void)
{
	int a=1,b=2;
	//&(a++);   error
	//该语句执行出错，a++是右值
	//Complex operator++(int) 后置运算符，返回的是对象
	
	&(++a);
	//该语句执行成功，++a是左值
	//Complex operator++()  前置运算符，返回的是引用
	
	//&(a+b);  error 右值
	//&100;   error  右值
	
	string s1("hello");
	string s2("world");

	//&(s1+s2); error
	//&string("hello");  error
	//&string();   error
	
	//万能引用
	//作为函数参数时，不能区分出传递过来的是左值还是右值
	const int & m=1;   //右值
	const int & n=a;   //左值

	//C++11提出右值引用，做转移操作
	int && ref=1; //右值引用只能绑定到右值
	//int && ref2=a;  error 右值引用不能绑定到左值上
	
	return 0;
}
