#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

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
		friend std::ostream & operator<<(std::ostream & os,const Point &rhs);
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

void test0()
{
	Point *pt=new Point(1,2);
	//显示：Point(int,int)
	shared_ptr<Point> sp(pt);
	
	shared_ptr<Point> sp2(sp);
	//执行复制构造或者赋值操作时，引用计数会+1，
	//当shared_ptr被销毁时，引用计数会-1。
	//只有当引用计数减为0时，才会真正销毁被托管的对象
	
	cout<<"*sp="<<*sp<<endl;
	//显示：*sp=(1,2)
	cout<<"*sp2="<<*sp2<<endl;
	//显示：*sp2=(1,2)
	

	//查看sp、sp2的引用计数
	cout<<"sp's use_count="<<sp.use_count()<<endl;
	//显示：sp's use_count=2
	cout<<"sp2's use_count="<<sp2.use_count()<<endl;
	//显示：sp2's use_count=2

	//局部变量
	{
		shared_ptr<Point> sp3(new Point(11,12));
		//显示：Point(int,int)
		cout<<"*sp3="<<*sp3<<endl;
		//显示：*sp3=(11,12)
		//执行赋值操作
		sp3=sp2;
		//将sp3本身托管的指针delete
		//显示：~Point()
		cout<<"执行赋值操作之后："<<endl;
		cout<<"*sp3="<<*sp3<<endl;
		//显示：*sp3=(1,2)
		
		//查看sp、sp2、sp3的引用计数
		cout<<"sp's use_count="<<sp.use_count()<<endl;
		//显示：sp's use_count=3
		cout<<"sp2's use_count="<<sp2.use_count()<<endl;
		//显示：sp2's use_count=3
		cout<<"sp3's use_count="<<sp3.use_count()<<endl;
		//显示：sp3's use_count=3
	}

	//查看sp、sp2的引用计数
	cout<<"sp's use_count="<<sp.use_count()<<endl;
	//显示：sp's use_count=2
	cout<<"sp2's use_count="<<sp2.use_count()<<endl;
	//显示：sp2's use_count=2
	return 0;
	//显示：~Point()
}

int main(void)
{
	test0();
	return 0;
}
