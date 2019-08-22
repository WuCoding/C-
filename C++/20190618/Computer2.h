#pragma once

//类的声明
class Computer//class的默认访问权限是private的
{
	public:
		void setBrand(const char*);
		void setPrice(double);
		void print();
	//通过private关键字表现封装的特性
	private:
	//类对象占据的空间只与数据成员有关，成员函数存储在程序代码区，不会占据对象空间
	char _brand[20];
	double _price;
};

