#include <iostream>
#include <vector>
#include <boost/ptr_container/ptr_container.hpp>  //boost库，存储指针的容器
using std::cout;
using std::endl;
using std::vector;

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

	//复制构造函数
	Point(const Point &rhs)
	: _ix(rhs._ix)
	, _iy(rhs._iy)
	{
		cout<<"Point(const Point &rhs)"<<endl;
	}

	//打印函数
	void print() const
	{
		cout<<"("<<_ix<<","<<_iy<<")"<<endl;
	}

	//设置数据成员_ix的值
	void setX(int ix)
	{
		_ix=ix;
	}

	//设置数据成员_iy的值
	void setY(int iy)
	{
		_iy=iy;
	}

	//析构函数
	~Point()
	{
		cout<<"~Point()"<<endl;
	}

private:
	//数据成员
	int _ix;
	int _iy;
};

int test0()
{
	//创建一个存储指针的容器，每个指针指向一个堆空间的对象
	vector<Point *> points
	{
		new Point(1,2),
		new Point(3,4),
		new Point(5,6)
	};
	//显示：Point(int,int)
	//	Point(int,int)
	//	Point(int,int)

	//将每个元素打印出来
	for(auto it=points.begin();it!=points.end();++it)
	{
		(*it)->print();
	}
	//显示：(1,2)
	//	(3,4)
	//	(5,6)

	return 0;
}

int test1()
{
	//boost库中的指针容器，<>中写的是指针指向的类型
#if 0
	//这种赋初始值的方式执行报错，只能用push_back来添加容器中的元素
	boost::ptr_vector<Point> points
	{
		new Point(1,2),
		new Point(3,4),
		new Point(5,6)
	};
#endif

#if 1	
	boost::ptr_vector<Point> points;
	points.push_back(new Point(1,2));
	points.push_back(new Point(3,4));
	//显示：Point(int,int)
	//	Point(int,int)
#endif

	for(auto it=points.begin();it!=points.end();++it)
	{
		//(*it)->print(); 不行
		//(*it).print(); 行
		it->print();// 行 不知道为啥可以，没找到源码
	}
	//显示：(1,2)
	//	(3,4)
	
	//显示：~Point()
	//	~Point()


	return 0;
}

int test2()
{
	//空间分配与对象的创建是分离的
	vector<Point> numbers;
	cout<<"numbers'capacity="<<numbers.capacity()<<endl;
	cout<<"numbers'size="<<numbers.size()<<endl;
	//显示：numbers'capacity=0
	//	numbers'size=0
	
	//空间开辟
	numbers.reserve(100);
	cout<<"numbers'capacity="<<numbers.capacity()<<endl;
	cout<<"numbers'size="<<numbers.size()<<endl;
	//显示：numbers'capacity=100
	//	numbers'size=0

	Point pt(1,2);
	//显示：Point(int,int)
	
	numbers.push_back(pt);
	//显示：Point(const Point &rhs)
	//对pt进行了复制，调用Point类的复制构造函数，复制构造
	//一个相同的对象放在vector容器开辟的空间里
	cout<<"numbers'capacity="<<numbers.capacity()<<endl;
	cout<<"numbers'size="<<numbers.size()<<endl;
	//显示：numbers'capacity=100
	//	numbers'size=1


	numbers[0].setX(10);
	numbers[0].setY(11);

	cout<<"numbers[0]=";
	numbers[0].print();
	//显示：numbers[0]=(10,11)

	cout<<"pt=";
	pt.print();
	//显示：pt=(1,2)
	
	//可见容器中的元素对象和压栈的元素对象不是一个对象，
	//改变容器中的元素值，不会改变压栈对象的值，压栈相
	//当于值传递
	
	//显示：~Point()
	//	~Point()

	return 0;
}

int main(void)
{
	//test0();
	//test1();
	test2();
	
	return 0;
}


