#include <math.h>

#include <iostream>
using std::cout;
using std::endl;
//友元函数之友元类
class Point;//类的前向声明

class Line
{
	public:
		//使用Point类的私有成员
		float distance(const Point & lhs,const Point & rhs);
		//改变Point类的私有成员
		void setPoint(Point * pt,int ix,int iy);

		//改变自己的数据成员
		void setZ(int iz)
		{
			_iz=iz;
		}
	private:
		int _iz;
};

//此处是Point类的实现
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

#if 0
		//注意友元关系是单向的，类A是类B的友元，可以访问类B的私有成员，但类B不是类A的友元，不能访问类A的私有成员
		void setZ(Line *line,int iz)
		{
			line->_iz=iz;
		}
#endif
		//友元函数之友元类
		friend class Line;//将Line类设为Point类的友元，Line类可以访问Point类的私有成员，但Point类不能访问Line类的私有成员（友元关系为单向的）；
	private:
		int _ix;
		int _iy;
};

//A->B (A是B的友元) ，B->C (B是C的友元)，A->C?(则A是C的友元吗)
//答：不是！！ 友元不具备传递性
//
//在C++中，友元确实破坏了类的封装性；
//但其使用是受到限制的：
//1. 友元是单向的
//2. 友元不具备传递性
//3. 友元不能被继承
//
//友元是把双刃剑，不要滥用

//Line类中成员函数的实现，使用Point类的私有成员
float Line::distance(const Point & lhs,const Point & rhs)
{
	//返回两点的距离
	return sqrt((lhs._ix-rhs._ix)*(lhs._ix-rhs._ix)+(lhs._iy-rhs._iy)*(lhs._iy-rhs._iy));
}

//Line类中成员函数的实现，改变Point类的私有成员
void Line::setPoint(Point * pt,int ix,int iy)
{
	pt->_ix=ix;
	pt->_iy=iy;
}

int main(void)
{
	Point pt1(1,2),pt2(3,4);

	pt1.print();
	cout<<"----->";
	pt2.print();

	//Line类是Point类的友元类
	Line line;
	//使用Point的私有成员
	cout<<"的距离是："<<line.distance(pt1,pt2)<<endl;
	//修改Point的私有成员
	cout<<"修改pt2："<<endl;
	line.setPoint(&pt2,6,6);
	cout<<"pt2=";
	pt2.print();
	cout<<endl;

	return 0;
}



