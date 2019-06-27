#include <math.h>

#include <iostream>
using std::cout;
using std::endl;
//友元函数之普通函数
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

		//友元函数之普通函数，普通函数在类中做友元声明
		friend float distance(const Point & lhs,const Point & rhs);

	private:
		int _ix;
		int _iy;
};

//普通函数的实现
float distance(const Point & lhs,const Point & rhs)
{
	//称为类的友元则可以访问类中的私有成员
	return sqrt((lhs._ix-rhs._ix)*(lhs._ix-rhs._ix)+(lhs._iy-rhs._iy)*(lhs._iy-rhs._iy));//求平方根函数
}
int main(void)
{
	Point pt1(1,2),pt2(3,4);

	pt1.print();
	cout<<"------>";
	pt2.print();
	cout<<"的距离是："<<distance(pt1,pt2)<<endl;

	return 0;
}
