#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
#include <algorithm>//算法库
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::copy;
using std::set;

//都采用了适配器设计模式
// stack  queue  prioty_queue
using std::ostream_iterator; //输出流迭代器
using std::back_insert_iterator;//在尾部添加元素
using std::front_insert_iterator;//在头部添加元素
using std::insert_iterator;//在任意位置添加元素

int main(void)
{
	//创建一个vector容器
	vector<int> numbers{1,2,3};

	//使用反向迭代器将容器中的元素打印出来
	for(auto rit=numbers.rbegin();rit!=numbers.rend();++rit)
	{
		cout<<*rit<<" ";
	}
	cout<<endl;
	//显示：3 2 1

	//创建一个list容器
	list<int> numbers2{11,12,13};

	//尾部插入迭代器back_insert_iterator底层调用的是push_back方法
	//适用容器  vector  deque  list
	//将list容器中的元素拷贝到vector容器中，使用尾部插入迭代器
	copy(numbers2.begin(),numbers2.end(),back_insert_iterator<vector<int>>(numbers));
	//将vector容器中的元素拷贝到绑定了标准输出流的输出流容器中
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：1 2 3 11 12 13

	//头部插入迭代器front_insert_iterator底层调用的是push_front方法
	//适用容器  deque  list
	//将vector容器中的元素拷贝到list容器中，不能将list容器的元素用
	//头部插入迭代器拷贝到vector中，因为vector不支持头部插入迭代器
	copy(numbers.begin(),numbers.end(),front_insert_iterator<list<int>>(numbers2));
	//将list容器中的元素拷贝到绑定了标准输出流的输出流容器中
	copy(numbers2.begin(),numbers2.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：13 12 11 3 2 1 11 12 13

	//任意位置添加元素insert_iterator迭代器，底层调用的是insert方法
	//创建一个set容器
	set<int> numbers3{22,23,24};
	//将vector容器中的元素拷贝到set容器中的指定位置
	copy(numbers.begin(),numbers.end(),insert_iterator<set<int>>(numbers3,++numbers3.begin()));
	//将set容器中的元素拷贝到绑定了标准输出流的输出流容器中
	copy(numbers3.begin(),numbers3.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：1 2 3 11 12 13 22 23 24

	return 0;
}
		
