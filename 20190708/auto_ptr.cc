#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::auto_ptr;

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
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}

		//析构函数
		~Point()
		{
			cout<<"~Point()"<<endl;
		}

		//友元函数声明
		friend std::ostream & operator<<(std::ostream &os,const Point &rhs);
	private:
		//数据成员
		int _ix;
		int _iy;
};

//输出运算符重构函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

int main(void)
{
	Point *pt=new Point(1,2);
	//显示：Point(int,int)
	auto_ptr<Point> ap(pt);
	cout<<"*ap="<<*ap<<endl;
	//显示：*ap=(1,2)
	cout<<"ap.get()="<<ap.get()<<endl;
	//显示：ap.get()=0x5632ddc91e70
	cout<<"pt="<<pt<<endl;
	//显示：pt=0x5632ddc91e70

	auto_ptr<Point> ap2(ap);
	//在语法上是复制，但底层已经发生了所有权的转移
	//语法形式与表达的语义是矛盾的，存在缺陷，C++11之后被弃用
	
	cout<<"*ap2="<<*ap2<<endl;
	//显示：*ap2=(1,2)
	cout<<"ap2.get()="<<ap2.get()<<endl;
	//显示:ap2.get()=0x5632ddc91e70
#if 0
	//导致程序崩溃
	cout<<"*ap="<<*ap<<endl;
	cout<<"ap.get()="<<ap.get()<<endl;
#endif
	auto_ptr<Point> ap3(new Point(3,4));
	//显示：Point(int,int)
	ap3=ap2;//发生所有权的转移
	//显示：~Point()
	cout<<"*ap3="<<*ap3<<endl;
	//显示：*ap3=(1,2)
	cout<<"ap3.get()="<<ap3.get()<<endl;
	//显示：ap3.get()=0x5632ddc91e70
#if 0
	//导致程序崩溃
	cout<<"*ap2="<<*ap2<<endl;
	cout<<"ap2.get()="<<ap2.get()<<endl;
#endif

	return 0;
	//显示：~Point()
}
