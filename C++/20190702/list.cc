#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;

//----------------------------------------list----------------------------------------
//打印容器中元素信息的函数模板
template <class Container>
void display(const Container &c)
{
	for(auto & elem:c){
		cout<<elem<<" ";
	}
	cout<<endl;
}

//自定义的重载了函数调用运算符的类，该类的对象被称为函数对象
struct Comparator
{
	//该函数只有一个函数运算符重载函数
	bool operator()(int x,int y) const
	{
		return x>y;
	}
};

void test0()
{
	//创建两个list容器
	list<int> numbers1{3,1,4,5,2};
	list<int> numbers2{11,21,14,15,8};

	cout<<"before sort numbers1:"<<endl;
	display(numbers1);//显示：3 1 4 5 2
	cout<<"before sort numbers2:"<<endl;
	display(numbers2);//显示：11 21 14 15 8
	
	//默认情况下按升序方式进行排序
	numbers1.sort();
	numbers2.sort();
	cout<<"after sort numbers1:"<<endl;
	display(numbers1);//显示：1 2 3 4 5
	cout<<"after sort numbers2:"<<endl;
	display(numbers2);//显示：8 11 14 15 21
#if 0
	//第一种定制化排序方式
	std::greater<int> gt;
	numbers1.sort(gt);//显示：5 4 3 2 1
#endif

#if 1
	//第二种定制化排序方式
	Comparator cmp;
	numbers1.sort(cmp);//显示：5 4 3 2 1
#endif

	cout<<"after DIY numbers1:";
	display(numbers1);
}

void test1()
{
	list<int> numbers1{3,1,4,5,2};
	list<int> numbers2{11,21,14,15,8};

	//----------------------------------------merge------------------------------------------
	//执行merge之后，numbers2中的元素全部进入到numbers1中去了，
	//将numbers2中的元素在numbers1的尾部插入，而numbers2中没有元素了
	numbers1.merge(numbers2);
	cout<<"after merge numbers1:";
	display(numbers1);//显示：3 1 4 5 2 11 21 14 15 8

	cout<<"after merge numbers2:";
	display(numbers2);//显示：            （啥也不显示）

	//---------------------------------------reverse-----------------------------------------
	//reverse将容器中的元素首尾颠倒
	numbers1.reverse();
	cout<<"after reverse numbers1:";
	display(numbers1);//显示：8 15 14 21 11 2 5 4 1 3
}

void test2()
{
	list<int> numbers1{3,1,4,5,2};
	list<int> numbers2{11,21,14,15,8};
	//----------------------------------------splice----------------------------------------
	auto it=numbers1.begin();
	++it;

	//插入的范围为左闭右开
	auto start=numbers2.begin();
	++start;
	auto finish=numbers2.end();
	--finish;

	numbers1.splice(it,numbers2,start,finish);
	cout<<"after splice numbers1:";
	display(numbers1);//显示：3 21 14 15 1 4 5 2
	cout<<"after splice numbers2:";
	display(numbers2);//显示：11 8

	//将本容器中的最后一个元素提到容器开头
	auto it2=numbers1.end();
	--it2;//it2此时指向容器最后一个元素

	numbers1.splice(numbers1.begin(),numbers1,it2);
	cout<<"after splice numbers1:";
	display(numbers1);//显示：2 3 21 14 15 1 4 5
}

int main(void)
{
	//test0();
	//test1();
	test2();

	return 0;
}

