#include <iostream>
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

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

//输出运算符重载函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

int test0()
{
	Point *pt=new Point(1,2);
	//显示：Point(int,int)
	//智能指针托管
	unique_ptr<Point> ap(pt);
	
	cout<<"*ap="<<*ap<<endl;
	//显示：*ap=(1,2)
	cout<<"ap.get()="<<ap.get()<<endl;
	//显示：ap.get()=0x560645772e70
	cout<<"pt="<<pt<<endl;
	//显示：pt=0x560645772e70

	//unique_ptr<Point> ap2(ap);   error unique_ptr不能进行复制或者赋值
	unique_ptr<Point> ap2(std::move(ap));//可以执行
	cout<<"*ap2="<<*ap2<<endl;
	//显示：*ap2=(1,2)
	cout<<"ap2.get()="<<ap2.get()<<endl;
	//显示：ap2.get()=0x560645772e70

#if 0
	//执行下列语句程序崩溃
	cout<<"*ap="<<*ap<<endl;
	cout<<"ap.get()="<<ap.get()<<endl;
#endif

	unique_ptr<Point> ap3(new Point(3,4));
	//显示：Point(int,int)
	cout<<"ap3.get()="<<ap3.get()<<endl;
	//显示：ap3.get()=0x5606457732a0

	Point *pt2=new Point(11,12);
	//显示：Point(int,int)
	cout<<"pt2="<<pt2<<endl;
	//显示：pt2=0x5606457732c0
	ap3.reset(pt2);//重置托管的指针，旧指针已经被delete
	//ap3=ap2;  error
	//显示：~Point()
	
#if 1
	cout<<"*ap3="<<*ap3<<endl;
	//显示：*ap3=(11,12)
	cout<<"ap3.get()="<<ap3.get()<<endl;
	//显示：ap3.get()=0x5606457732c0
#endif
	return 0;
	//显示：~Point()
	//	~Point()
}

unique_ptr<Point> getPoint()  //返回一个托管Point类型指针的智能指针
{
	unique_ptr<Point> up(new Point(22,23));
	//显示：Point(int,int)
	cout<<"*up="<<*up<<endl;
	//显示：*up=(22,23)
	return up;//调用unique_ptr的移动构造函数
}

int test1()
{
	unique_ptr<Point> up=getPoint();
	//unique_ptr<Point> up2=up;
	
	//unique_ptr可以放入容器之中，需要采用移动语义
	using PointPtr=unique_ptr<Point>;
	vector<PointPtr> points;//可以代替指针容器
	points.push_back(std::move(up));

	cout<<"*points[0]="<<*points[0]<<endl;
	//显示：*points[0]=(22,23)

	points.emplace_back(new Point(11,12));//发生了隐式转换
	//显示：Point(int,int)
	cout<<"*points[1]="<<*points[1]<<endl;
	//显示：*points[1]=(11,12)

	return 0;
	//显示：~Point()
	//	~Point()
}

int main(void)
{
	//test0();
	test1();

	return 0;
}

