#include <math.h>

#include <iostream>
using std::cout;
using std::endl;
//友元函数之成员函数
class Point;//类的前向声明

//Line类
class Line
{
	public:
		float distance(const Point & lhs,const Point & rhs);
};

//Point类
class Point
{
	public:
	//构造函数
	Point(int ix=0,int iy=0)
	: _ix(ix)
	, _iy(iy)
	{
		cout<<"Point(int,int)"<<endl;
	}

	void print() const
	{
		cout<<"("<<_ix<<","<<_iy<<")";
	}

	//友元函数之成员函数
	friend float Line::distance(const Point & lhs,const Point & rhs);
	private:
		int _ix;
		int _iy;
};
//成员函数的实现
float Line::distance(const Point & lhs,const Point & rhs)
{
	return sqrt((lhs._ix-rhs._ix)*(lhs._ix-rhs._ix)+(lhs._iy-rhs._iy)*(lhs._iy-rhs._iy));
}


int main(void)
{
	Point pt1(1,2),pt2(3,4);

	pt1.print();
	cout<<"---->";
	pt2.print();
	cout<<"的距离是："<<Line().distance(pt1,pt2)<<endl;//Line()为匿名对象，这是个临时对象
	Line line;
	cout<<"的距离是："<<line.distance(pt1,pt2)<<endl;//line是有名对象这不是个临时对象

	return 0;
}































