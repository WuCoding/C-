#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

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

//输出运算符重构函数的实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

int main(void)
{
	//弱引用智能指针
	weak_ptr<Point> wp;//weak_ptr辅助shared_ptr
	{
		shared_ptr<Point> sp(new Point(1,2));
		//weak_ptr进行复制或者赋值时，不会导致引用计数+1，
		//但它知道所托管的对象是否存活
		//weak_ptr没有提供访问资源的接口
		//如果要访问资源必须提升成为shared_ptr使用

		wp=sp;  //weak_ptr=shared_ptr

		cout<<"wp's use_count="<<wp.use_count()<<endl;
		cout<<"sp's use_count="<<sp.use_count()<<endl;

		cout<<"wp's expired="<<wp.expired()<<endl;

		shared_ptr<Point> sp2=


