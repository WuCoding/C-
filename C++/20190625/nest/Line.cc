#include "Line.h"

#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

class Line::LineImpl
{
	//Point类只为LineImpl服务
	//希望隐藏Point的实现==》设计模式pimpl
	class Point//内含类
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
			//析构函数
			~Point()
			{
				cout<<"~Point()"<<endl;
			}
		private:
			int _ix;
			int _iy;
	};
	public:
		//构造函数
		LineImpl(int x1,int y1,int x2,int y2)
		: _pt1(x1,y1)
		, _pt2(x2,y2)
		{
			cout<<"LineImpl(int,int,int,int)"<<endl;
		}
		//打印函数
		void printLineImpl() const
		{
			_pt1.print();
			cout<<"---->";
			_pt2.print();
			cout<<endl;
		}
		//析构函数
		~LineImpl()
		{
			cout<<"~LineImpl()"<<endl;
		}
	private:
		//LineImpl类中的数据成员为Point类的对象
		Point _pt1;
		Point _pt2;
};
//Line类中的成员函数的实现
//Line类的构造函数，Line类的数据成员只有一个LineImpl类的指针
Line::Line(int x1,int y1,int x2,int y2)
: _pimpl(new LineImpl(x1,y1,x2,y2))
{
	cout<<"Line(int,int,int,int)"<<endl;
}

//Line类的析构函数
Line::~Line()
{
	if(_pimpl!=nullptr)
	{
		delete _pimpl;
		_pimpl=nullptr;
	}
}
//Line类中的打印函数
void Line::printLine() const
{
	_pimpl->printLineImpl();
}






































