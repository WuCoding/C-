#include <iostream>
using std::cout;
using std::endl;
//一个类的数据成员为另一个类的对象，即对象成员
class Point
{
	public:
	//构造函数
	Point(int ix=0,int iy=0)
	: _ix(ix)
	, _iy(iy)
	{
		cout<<"Point(int=0,int=0)"<<endl;
	}
	
	void setX(int ix)
	{
		_ix=ix;
	}

	void print()
	{
		cout<<"("<<this->_ix<<","<<this->_iy<<")";
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

class Line
{
	public:
	//构造函数
	//对象成员要放在初始化列表中进行初始化，如果忘记初始化，系统会自动调用相应类型的默认构造函数
	Line(int x1,int y1,int x2,int y2)
	: _pt1(x1,y1)
	, _pt2(x2,y2)
	{
		cout<<"Line(int,int,int,int)"<<endl;
	}

	void printLine()
	{
		_pt1.print();
		cout<<"--->";
		_pt2.print();
		cout<<endl;
	}
	private:
	//数据成员是两个类的对象
	Point _pt1;
	Point _pt2;
};

int main(void)
{
	Line line(1,2,3,4);
	line.printLine();

	return 0;
}

