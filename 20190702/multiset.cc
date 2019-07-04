#include <math.h>

#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::multiset;
using std::string;

//打印容器元素信息的函数模板
template <class Container>
void display(const Container &c)
{
	for(auto & elem:c){
		cout<<elem<<" ";
	}
	cout<<endl;
}

void test0()
{
	//默认情况下按升序方式进行排列
	
	//创建multiset容器
	multiset<int> numbers{4,1,2,7,9,6,5,1,3,2,1,9,8};
	//打印容器中元素信息
	display(numbers);//显示：1 1 1 2 2 3 4 5 6 7 8 9 9

	//multiset不支持下标访问运算符，所以下条语句执行错误
	//cout<<numbers[0]<<endl;
	
	//使用迭代器访问容器中的元素
	multiset<int>::iterator it=numbers.begin();
	cout<<"*it="<<*it<<endl;//显示：*it=1

	//multiset中的元素不能进行修改，是只读的，所以下条语句执行错误
	//*it=10;
	
	//查找元素，count用来判断元素是否在multiset之中，时间复杂度为0(logN)
	size_t cnt=numbers.count(1);
	cout<<"1 是否存在："<<cnt<<endl;//显示：1 是否存在：3

	cnt=numbers.count(10);
	cout<<"10 是否存在："<<cnt<<endl;//显示：10 是否存在：0

	//find查找到了返回的是迭代器，还可以访问元素，时间复杂度为0(logN)
	multiset<int>::iterator it2=numbers.find(2);
	//找到时返回指向该元素的迭代器，未找到则返回end迭代器
	if(it2!=numbers.end()){//找到元素
		cout<<" 查找到了关键字 2"<<endl;
		cout<<"*it2="<<*it2<<endl;
	}//显示：查找到了关键字 2   *it2=2

	it2=numbers.find(10);
	if(it2==numbers.end()){//未找到元素
		cout<<"没有查找到关键字 10"<<endl;
	}//显示：没有查找到关键字 10

	//添加新元素insert，insert返回的是迭代器
	auto ret=numbers.insert(2);
	//打印该迭代器指向的值
	cout<<*ret<<endl;//显示：2

	//范围查找
	//第一种范围查找方法
	auto it1=numbers.lower_bound(1);//指向第一个1出现的位置
	it2=numbers.upper_bound(1);//指向最后一个1出现的下一个位置
	while(it1!=it2){
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;//显示：1 1 1
	
	//第二种范围查找方法
	auto ret2=numbers.equal_range(2);
	cout<<*ret2.first<<endl;//显示：2
	cout<<*ret2.second<<endl;//显示：3
}

void test1()
{
	//创建一个multiset容器，第二个系数为元素在容器中的排列顺序
	multiset<int,std::greater<int>> numbers{4,1,2,7,9,6,5,1,3,2,1,9,8};
	//打印该容器中的元素信息
	display(numbers);//显示：9 9 8 7 6 5 4 3 2 2 1 1 1

	//multiset不支持下标访问运算符，所以下条语句将报错
	//cout<<numbers[0]<<endl;
	
	//用迭代器来访问容器中元素信息
	multiset<int>::iterator it=numbers.begin();
	cout<<"*it="<<*it<<endl;//显示：*it=9

	//multiset中的元素不能进行修改，是只读的，所以下条语句将报错
	//*it=10;
	
	//查找元素，count用来判断元素是否在multiset之中，时间复杂度为0(logN)
	size_t cnt=numbers.count(1);
	cout<<"1 是否存在："<<cnt<<endl;//显示：1 是否存在：3

	cnt=numbers.count(10);
	cout<<"10 是否存在："<<cnt<<endl;//显示：10 是否存在：0

	//find查找到了返回的是迭代器，还可以访问元素，时间复杂度为0(logN)
	multiset<int>::iterator it2=numbers.find(2);
	//找到了返回指向目标元素的迭代器，未找到则返回end迭代器
	if(it2!=numbers.end()){
		cout<<" 查找到了关键字 2"<<endl;
		cout<<"*it2="<<*it2<<endl;
	}//显示：查找到了关键字 2  *it2=2

	it2=numbers.find(10);
	if(it2==numbers.end()){
		cout<<"没有查找到关键字 10"<<endl;
	}//显示：没有查找到关键字 10
}

//自定义类型作为multiset容器的元素类型
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

		//输出运算符重载函数的友元声明
		friend std::ostream & operator<<(std::ostream & os,const Point & rhs);
	private:
		//数据成员
		int _ix;
		int _iy;
};

//输出运算符重载函数的实现
std::ostream & operator<<(std::ostream & os,const Point & rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

//Point类型的小于运算符重载函数
bool operator<(const Point &lhs,const Point &rhs)
{
	return lhs.getDistance()<rhs.getDistance();
}

//自定义重载了函数调用运算符的类
struct Comparator//struct关键字定义的类成员默认权限为public
{
	//该类中只有一个函数调用运算符重载函数
	bool operator()(const Point & lhs,const Point &rhs) const
	{
		return lhs.getDistance()>rhs.getDistance();
	}
};

void test2()
{
	//用自定义类型和自定义排列函数来创建multiset容器
	multiset<Point,Comparator> points{
		Point(1,2),
		Point(3,4),
		Point(4,5),
		Point(-1,3),
		Point(-2,-4),
		Point(1,2)
	};
	//还是和上一个一样，先执行构造函数，再执行复制构造函数，再执行析构函数
	//再在程序结束时，执行析构函数
	
	//打印容器中元素信息
	display(points);
	//显示：(4,5)(3,4)(-2,-4)(-1,3)(1,2)(1,2)
	//有重复的元素信息
}

int main(void)
{
	//test0();
	//test1();
	test2();

	return 0;
}














































