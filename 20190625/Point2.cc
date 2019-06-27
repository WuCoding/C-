#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

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

		//打印函数
		void print() const
		{
			cout<<"("<<_ix<<","<<_iy<<")";
		}

		//类型转换函数
		//将Point类型转换为int类型
		operator int()
		{
			cout<<"operator int()"<<endl;
			return _ix;
		}

#if 0
		//将Point类型转换为double类型
		operator double()
		{
			return _ix*_iy;
		}
#endif
		//输出运算符<<重载函数友元函数
		//friend std::ostream & operator<<(std::ostream & os,const Point & rhs);

	private:
		int _ix;
		int _iy;
};
#if 0
//输出运算符<<重载函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}
#endif

int main(void)
{
	Point pt1(1,2),pt2(3,4);

	cout<<"pt1="<<pt1<<endl;//如果没有输出运算符重构函数，则会自动执行int类型转换函数，然后将int类型数据来输出

	return 0;
}







































