#include <iostream>
using std::cout;
using std::endl;

class Point
{
	public:
	//如果没有显示定义构造函数时，系统会自动提供一个默认构造函数
	Point()
	{
		_ix=0;
		_iy=0;
		cout<<"Point()"<<endl;
	}
	//构造函数可以重载
	//如果显式定义了有参构造函数时，系统就不会再自动提供默认构造函数
	//如果还希望通过默认函数构建对象，则必须显式提供一个默认构造函数
	Point(int ix,int iy)
	{
		_ix=ix;
		_iy=iy;
		cout<<"Point(int,int)"<<endl;
	}


