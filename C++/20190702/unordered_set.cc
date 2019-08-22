#include <math.h>

#include <iostream>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_set;

//打印容器中元素信息的函数模板
template <class Container>
void display(const Container & c)
{
	for(auto & elem:c){
		cout<<elem<<" ";
	}
	cout<<endl;
}

void test0()
{
	//unordered_set不能存放关键字相同的元素
	//元素是无序的
	unordered_set<int> numbers{3,2,5,7,9,2,3,1,3};
	//打印unordered_set容器中元素信息
	display(numbers);//显示：1 9 7 5 2 3
}

//自定义类型，作为unordered_set容器元素的类型
class Point
{
	public:
		//构造函数
		Point(int ix,int iy)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}

		//复制构造函数
		Point(const Point & rhs)
		: _ix(rhs._ix)
		, _iy(rhs._iy)
		{
			cout<<"Point(const Point &)"<<endl;
		}

		//析构函数
		~Point()
		{
			cout<<"~Point()"<<endl;
		}

		//获得点到原点的距离
		double getDistance() const
		{
			return sqrt(_ix*_ix+_iy*_iy);
		}

		//获得Point类的私有数据成员的数值
		int getX() const
		{
			return _ix;
		}
		int getY() const
		{
			return _iy;
		}

		//友元函数声明
		friend std::ostream & operator<<(std::ostream &os,const Point &rhs);
		friend bool operator==(const Point &lhs,const Point &rhs);
	private:
		//数据成员
		int _ix;
		int _iy;
};

//Point类的输出运算符重载函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

//Point类的相等运算符重载函数实现
bool operator==(const Point & lhs,const Point & rhs)
{
	return lhs._ix==rhs._ix && lhs._iy==rhs._iy;
}

//------------------------------------------------------
namespace std
{
	template<>
	struct hash<Point>
	{
		//获得一个Point类对象的hash值
		size_t operator()(const Point & point) const
		{
			int x=point.getX();
			int y=point.getY();
			return (x*x-1)^(y*y-1);
		}
	};
}//end of namespace std

void test1()
{
	//空间的消耗是元素的2倍
	//以空间换时间
	//hash表，有个填充因子，一般为0.5，超过就要rehash
	
	//创建unordered_set容器
	unordered_set<Point> points{
		Point(1,2),
		Point(3,4),
		Point(5,6),
		Point(7,8),
		Point(3,4)
	};
	//先调用构造函数，再调用复制构造函数，再析构，在程序执行结束时，再调用析构
	//打印容器中的元素信息
	display(points);//显示：(7,8)(3,4)(5,6)(1,2)
	//无序显示
	
	//对于unordered_set容器的迭代器
	auto it=points.begin();
	++it;// 只支持向前遍历
	cout<<"*it="<<*it<<endl;//显示：*it=(3,4)

	auto it2=points.end();
	//--it; 该语句执行错误，因为unordered_set容器的迭代器
	//不支持向后遍历
	
	//unordered_set容器，不支持下标运算符
	//points[0]; 该语句将会执行出错
	
	//查找元素
	//count和find时间复杂度为0(1)
	size_t cnt=points.count(Point(-1,2));
	if(cnt){//如果cnt不为0
		cout<<"查找成功！"<<endl;
	}else{//如果cnt为0
		cout<<"查找失败！"<<endl;
	}
}

int main(void)
{
	//test0();
	test1();

	return 0;
}












































