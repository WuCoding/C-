#include <math.h>

#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::set;
using std::string;

//------------------------------------------set容器-----------------------------------------

//打印容器中元素的函数模板
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
	
	//set中不能存放关键字相同的元素，可用来去重
	//set的底层实现采用的是红黑树---->近似的平衡二叉树（AVL树）
	//                     ---->查找元素的时间复杂度为0(logN)---->二分查找
	
	//红黑树的特点：
	//    1.节点不是红色就是黑色
	//    2.根节点是黑色的
	//    3.叶子节点都是黑色的
	//    4.不能有两个连续的红色节点
	//    5.从根节点到任意一个叶子节点的路径上，黑色节点数目相同
	
	//创建一个set容器，将重复元素去掉，并默认按从大到小顺序排列
	set<int> numbers{4,1,2,7,9,6,5,1,3,2,1,9,8};
	//打印该容器中的元素
	display(numbers);//显示：1 2 3 4 5 6 7 8 9 

	//注意：set不支持下标访问运算符，所以下面语句是错误的
	//cout<<numbers[0]<<endl;
	
	//set容器中的迭代器使用
	set<int>::iterator it=numbers.begin();
	cout<<"*it="<<*it<<endl;//显示：*it=1

	//注意：set中的元素不能进行修改，元素是只读的（因为底层为红黑树），
	//所以下面语句是错误的
	//*it=10;
	
	//-------------------------查找元素--------------------------
	//--------------count用来判断元素是否在set之中---------------
	size_t cnt=numbers.count(1); //判断是否含有某元素的时间复杂度为0(logN)二分法查找
	cout<<"1是否存在："<<cnt<<endl;//显示：1是否存在：1 

	cnt=numbers.count(10);
	cout<<"10是否存在："<<cnt<<endl;//显示：10是否存在：0

	//--------find查找到了返回的是迭代器，还可以访问元素--------
	set<int>::iterator it2=numbers.find(2);//时间复杂度为0(logN)
	//如果存在则find返回的是指向该元素的迭代器，如果不存在，则返回容器的end迭代器
	if(it2!=numbers.end()){
		cout<<"查找到了关键字 2"<<endl;
		cout<<"*it2="<<*it2<<endl;
	}//显示：查找到了关键字 2  *it2=2

	it2=numbers.find(10);
	if(it2==numbers.end()){
		cout<<"没有查找到关键字 10"<<endl;
	}//显示：没有查找到关键字 10

	//-----------------------添加新元素---------------------------
	std::pair<set<int>::iterator,bool> ret=numbers.insert(2);
	//如果插入的元素已经存在在容器中，则插入失败
	//ret容器存储了2个值，first为set<int>的迭代器类型，second为bool类型
	if(ret.second){   //ret.second为真，表示添加成功
		cout<<"set添加元素成功！"<<endl;
		cout<<*ret.first<<endl;  //打印插入的元素
	}else{
		cout<<"set添加元素失败！"<<endl;
		cout<<*ret.first<<endl;
	}//显示：set添加元素失败  2
}

void test1()//-------------------------------pair容器的使用-----------------------------
{
	//<>中存放入的两个数据的类型
	std::pair<int,string> pairs(100,"Jackie");
	//通过first和second来访问这两个数据
	cout<<pairs.first<<"----->"<<pairs.second<<endl;
	//显示：100----->Jackie
}

void test2()
{
	//<>中第二个系数是要求的set容器中元素的排列方式，greater表示按照int类型降序排列
	set<int,std::greater<int>> numbers{4,1,2,7,9,6,5,1,3,2,1,9,8};
	//打印容器中的元素信息
	display(numbers);//显示：9，8，7，6，5，4，3，2，1

	//set不支持下标访问运算符，所以下条语句会执行出错
	//cout<<numbers[0]<<endl;
	
	//但可以用迭代器来访问set容器中的元素
	set<int>::iterator it=numbers.begin();
	cout<<"*it="<<*it<<endl;//显示：*it=9

	//注意：因为set中的元素是只读的，不能进行修改（因为底层实现为红黑树），
	//所以下条语句执行出错
	//*it=10;
	
	//查找元素，count用来判断元素是否在set之中，时间复杂度为0(logN)
	size_t cnt=numbers.count(1);
	cout<<"1 是否存在："<<cnt<<endl;//显示：1 是否存在：1

	cnt=numbers.count(10);
	cout<<"10 是否存在："<<cnt<<endl;//显示：10 是否存在：0

	//find查找到了返回的是迭代器，还可以访问元素，时间复杂度为0(logN)
	set<int>::iterator it2=numbers.find(2);
	//找到元素返回的是指向该元素的迭代器，未找到则返回end迭代器
	if(it2!=numbers.end()){
		cout<<"查找到了关键字 2"<<endl;
		cout<<"*it2="<<*it2<<endl;
	}//显示：查找到了关键字 2   *it2=2
	
	it2=numbers.find(10);
	if(it2==numbers.end()){
		cout<<"没有查找到关键字 10"<<endl;
	}//显示：没有查找到关键字 10

	//添加新元素，insert
	//<>中写有要存储的两个数据的类型
	std::pair<set<int>::iterator,bool> ret=numbers.insert(2);
	//如果要添加的元素，容器中已经存在，则添加失败
	if(ret.second){//如果ret第二个数据为真，表示插入成功
		cout<<"set添加元素成功！"<<endl;
		cout<<*ret.first<<endl;
	}else{//添加元素失败
		cout<<"set添加元素失败！"<<endl;
		cout<<*ret.first<<endl;
	}//显示：set添加元素失败！   2

	//该语句执行成功，说明set容器的迭代器可执行自减操作
	auto it3=numbers.end();
	--it3;
	cout<<"*it3="<<*it3<<endl;
}

//用自己的设计的类型对象作为set容器中的元素
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
		Point(const Point &rhs)
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

		//获取点到原点的距离
		double getDistance() const
		{
			return sqrt(_ix*_ix+_iy*_iy);
		}

		//输出运算符重载函数的友元声明
		friend std::ostream & operator<<(std::ostream & os,const Point &rhs);
	private:
		//数据成员
		int _ix;
		int _iy;
};

//输出运算符重载函数的实现
std::ostream & operator<<(std::ostream & os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

//Point类的小于判断符重载，根据到原点距离大小来决定
bool operator<(const Point &lhs,const Point &rhs)
{
	return lhs.getDistance()<rhs.getDistance();
}

//创建一个重载了函数调用运算符的类，该类的对象被称为函数对象
struct Comparator //struct关键字创建的类，默认成员权限为public
{
	//该类中只有一个重载了函数调用运算符的成员函数
	bool operator()(const Point & lhs,const Point & rhs) const
	{
		return lhs.getDistance()>rhs.getDistance();
	}
};

void test3()
{
	//创建一个set容器，元素类型为用户自定义的Point类型，排列方式为
	//用户自己创建的重载了函数调用运算符的类型
	set<Point,Comparator> points{
		Point(1,2),
		Point(3,4),
		Point(4,5),
		Point(-1,3),
		Point(-2,-4),
		Point(1,2)
	};
	//根据显示结果表明，在创建容器时先将临时对象执行构造函数，
	//然后将临时对象赋值给容器中的对象，此时执行复制构造函数，
	//然后将临时对象销毁，执行析构函数，在程序结束时，执行析构
	//函数，将容器中的元素对象销毁。
	
	//打印该容器元素信息
	display(points);
	//显示：(4,5) (3,4) (-2,-4) (-1,3) (1,2)
	//按照到原点距离由大到小排列
}

int main(void)
{
	//test0();
	//test1();
	//test2();
	test3();

	return 0;
}

	








































