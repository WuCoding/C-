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
		cout<<"Point(int=0,int=0)"<<endl;
	}
	//赋值构造函数，Point a=b;
	Point(const Point &rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout<<"Point(const Point &)"<<endl;
	}
	//系统提供的复制构造函数
	//问题1：形参中的引用符号不能删除，如果删除会造成复制构造函数无穷递归调用，直到栈溢出，程序崩溃
	//问题2：形参中的const关键字可以去掉不？
	//不可以去掉，如果去掉，当传递过来的参数是右值时，就会报错，只有const &类型才能既接左值，又接右值
	//Point(const Point rhs) error
	//Point(Point &rhs) error
	
	//赋值运算函数
	Point & operator=(const Point &rhs)//括号里是右操作数，也要用const &类型来接左值或右值，返回值是对象的引用是为了实现连续赋值 a=b=c=d
	{
		cout<<"Point & operator=(const Point &)"<<endl;
		this->_ix=rhs._ix;
		this->_iy=rhs._iy;
		return *this;
	}

	//this指针代表的是当前对象，是当前对象的地址值，是个常量指针不能改变指向(Point * const this)，在调用成员函数时，函数接口通过this来获得调用者的信息
	void print()
	{
		//this=0x123ab3c7 错误 this的值不能发生改变
		cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
	}
	private:
	int _ix;
	int _iy;
};

int main(void)
{
	//int & ref=1; 错误，非const引用不能绑定到右值
	const int &ref2=1;//const引用可以绑定到右值
	cout<<"ref2="<<ref2<<endl;

	Point pt1(1,2);
	cout<<"pt1=";
	pt1.print();

	Point pt2(3,4);
	cout<<"pt2=";
	pt2.print();//事实上成员函数指令也和普通函数指令一样存在程序代码区，调用函数即转到该函数在程序代码区的入口，Point::print(&pt2) &pt2就是this指针

	Point pt3(5,6);
	
	//运用赋值运算符函数
	pt2=pt1=pt3;
	pt2.operator=(pt1);//Point::operator=(&pt2,pt1);
	cout<<"pt2=";
	pt2.print();

	return 0;
}

	
