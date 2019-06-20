#include <iostream>
using std::cout;
using std::endl;
//对于类中常量数据成员的使用
class Point
{
	public:
	//构造函数
	Point(int ix=0,int iy=0)
	: _ix(ix) //常量数据成员要在初始化表达式（初始化列表）中进行初始化
	, _iy(iy) //而不能在构造函数函数体中进行赋值
	{
		cout<<"Point(int=0,int=0)"<<endl;
		//下列赋值语句将发生报错
		//_ix=ix;
		//_iy=iy;
	}

	void print()
	{
		cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
	}

	//析构函数
	~Point()
	{
		cout<<"~Point()"<<endl;
	}
	private:
	const int _ix;
	const int _iy;
};


int main(void)
{
	Point pt1(1,2);
	cout<<"pt1=";
	pt1.print();
	
	return 0;
}


