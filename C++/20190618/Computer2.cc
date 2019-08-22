#include "Computer2.h"

#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

//类的实现,(类的声明在头文件中)
void Computer::setBrand(const char *brand)
{
	strcpy(_brand,brand);
}

void Computer::setPrice(double price)
{
	_price=price;
}

void Computer::print()
{
	cout<<"brand:"<<_brand<<endl
		<<"price:"<<_price<<endl;
}











