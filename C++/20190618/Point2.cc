#include <iostream>
using std::cout;
using std::endl;

class Point
{
	public:
		//Point类的构造函数
		Point(int ix=0,int iy=0)
		:_ix(ix)//在这里才是对数据成员的初始化，这是初始化表达式，放在构造函数语句中的话是
		,_iy(iy)//赋值，而不是初始化
		{
			//赋值语句，而不是初始化语句
			//_ix=ix;
			//_iy=iy;
			cout<<"Point(int=0,int=0)"<<endl;
		}

		void print()
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}
	private:
		int _ix;
		int _iy;
};

int main(void)
{
	Point pt1(1,2);
	pt1.print();

	Point pt2;//用构造函数的默认形参值
	pt2.print();
	
	return 0;
}
