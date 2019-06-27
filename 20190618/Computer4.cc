#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class Computer
{
	public:
	//构造函数
	Computer(const char *brand,double price)//注意这里用const char因为如果用字符串常量来赋值，用char型形参来接就会报错，而用const char型形参来接则无论实参是变量还是常量都不会报错，所以要记住运用const型形参
