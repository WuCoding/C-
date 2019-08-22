#include <math.h>

#include <iostream>
#include <algorithm>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point
{
	public:
		//构造函数
		Point(int ix,int iy)
		: _ix(ix)
		, _iy(iy)
		{}

		//获得到原点的距离
		double getDistance() const
		{
			return sqrt(_ix*_ix+_iy*_iy);
		}

		//友元函数声明
		//重载输出运算符
		friend std::ostream & operator<<(std::ostream & os,const Point & rhs);
		//重载相等运算符
		friend bool operator==(const Point &lhs,const Point &rhs);
		//重载小于运算符
		friend bool operator<(const Point &lhs,const Point &rhs);
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

//相等运算符重载函数实现
bool operator==(const Point &lhs,const Point &rhs)
{
	return (lhs._ix==rhs._ix)&&(lhs._iy==rhs._iy);
}

//小于运算符的重构函数实现
bool operator<(const Point &lhs,const Point &rhs)
{
	return lhs.getDistance()<rhs.getDistance();
}

//重载了函数调用运算符的类，该类的对象为函数对象
struct PointComparator
{
	bool operator()(const Point &lhs,const Point &rhs) const
	{
		return lhs.getDistance()<rhs.getDistance();
	}
};
#if 1
void display(int &number)
{
	cout<<number<<" ";
}
int test0()
{
	vector<int> numbers{1,8,10,9,2,4,3,5};

#if 0
	for_each(numbers.begin(),numbers.end(),display);
	//显示：1 8 10 9 2 4 3 5
#endif
	
#if 1	
	//lambda表达式
	for_each(numbers.begin(),numbers.end(),[](int number){
			cout<<number<<" ";
	});
	//显示：1 8 10 9 2 4 3 5
#endif
	cout<<endl;

	//std::find 时间复杂度为0(N)
	auto it=std::find(numbers.begin(),numbers.end(),10);
	//find查找到返回指向该元素的迭代器
	//未找到则返回end迭代器
	if(it!=numbers.end()){//找到了目标元素
		cout<<"*it="<<*it<<endl;
	}else{//未找到目标元素
		cout<<"元素没有找到！"<<endl;
	}
	//显示：*it=10

	//排序
	std::sort(numbers.begin(),numbers.end());
	for_each(numbers.begin(),numbers.end(),[](int number){
			cout<<number<<" ";
	});
	cout<<endl;
	//显示：1 2 3 4 5 8 9 10

	//二分查找0(logN)
	auto it2=std::lower_bound(numbers.begin(),numbers.end(),10);
	cout<<"*it2="<<*it2<<endl;
	//显示：*it2=10
	
#if 0
	bool isexit=std::binary_search(numbers.begin(),numbers.end(),10);
	cout<<"isexit="<<isexit<<endl;
	//显示：isexit=1
#endif

#if 1
	bool isexit=std::binary_search(numbers.begin(),numbers.end(),11);
	cout<<"isexit="<<isexit<<endl;
	//显示：isexit=0
#endif

}
#endif
int test1(void)
{
	//以自定义类型为vector容器的元素类型
	vector<Point> numbers{
		Point(1,2),
		Point(7,8),
		Point(5,6),
		Point(15,6),
		Point(1,12)
	};

	//lambda表达式---->匿名函数
	for_each(numbers.begin(),numbers.end(),[](const Point &point){
			cout<<point<<" ";
	});
	cout<<endl;
	//显示：(1,2) (7,8) (5,6) (15,6) (1,12)

	//std::find 时间复杂度为0(N)
	auto it=std::find(numbers.begin(),numbers.end(),Point(7,8));
	//查到目标元素，返回该元素迭代器，未查到返回end迭代器
	if(it!=numbers.end())
	{//查到目标元素
		cout<<"*it="<<*it<<endl;
	}else{//未查到目标元素
		cout<<"元素没有找到！"<<endl;
	}
	//显示：*it=(7,8)

	//堆排
#if 0
	std::sort(numbers.begin(),numbers.end(),PointComparator());
	//显示：(1,2) (5,6) (7,8) (1,12) (15,6)
#endif

#if 1
	std::sort(numbers.begin(),numbers.end(),
			[](const Point &lhs,const Point &rhs){
			return lhs.getDistance()<rhs.getDistance();
	});
	//显示：(1,2) (5,6) (7,8) (1,12) (15,6)
#endif

	for_each(numbers.begin(),numbers.end(),[](const Point &point){
			cout<<point<<" ";
	});
	cout<<endl;

	//二分查找 0(logN)
	auto it2=std::lower_bound(numbers.begin(),numbers.end(),Point(7,8),
			PointComparator());
	//输出返回的迭代器
	cout<<"*it2="<<*it2<<endl;
	//显示：*it2=(7.8)

#if 0
	bool isexit=std::binary_search(numbers.begin(),numbers.end(),Point(1,12));
	cout<<"isexit="<<isexit<<endl;
	//显示：isexit=1
#endif

#if 1
	bool isexit=std::binary_search(numbers.begin(),numbers.end(),Point(1,1));
	cout<<"isexit="<<isexit<<endl;
	//显示：isexit=0
#endif

	return 0;
}

int main(void)
{
	test0();
	//test1();

	return 0;
}
			










