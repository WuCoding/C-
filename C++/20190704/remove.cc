#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::remove;
using std::ostream_iterator;

void test0()
{
	vector<int> numbers{3,2,1,66,7,4,9,66,10,66};
	//将vector容器中的元素拷贝到绑定了标准输出流的输出流容器
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：3 2 1 66 7 4 9 66 10 66

	//remove的过程中，没有直接删除元素
	//如果直接删除元素，可能会导致迭代器出现错误
	auto it=remove(numbers.begin(),numbers.end(),66);
	//remove算法是不看底层什么容器来实现，而是直接对迭代器进行操作
	
	//打印容器中的元素
	for(auto & elem:numbers)
	{
		cout<<elem<<" ";
	}
	cout<<endl;
	//可见容器中并未删除元素，只是将非目标元素（不是要删除的元素）往前
	//移动。
	//显示：3 2 1 7 4 9 10 66 10 66

	//要删除元素 erase-remove惯用法
	numbers.erase(it,numbers.end());
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//显示：3 2 1 7 4 9 10
}
//一般情况下，在遍历容器元素的过程中，不要做删除元素和添加元素的操作
//防止发生迭代器失效的问题

void test1()
{
	vector<int> numbers;
	numbers.push_back(1);
	bool flag=true;
	cout<<"numbers's size="<<numbers.size();
	cout<<"numbers's capacity="<<numbers.capacity();

	//迭代器失效
	for(auto it=numbers.begin();it!=numbers.end();++it)
	{
		cout<<*it<<" ";
		if(flag){
			numbers.push_back(2);
			flag=false;
		}
	}
	//因为在执行push_back的语句时，发生了容器扩容，it指向的还是旧空间的第一个
	//元素，迭代器已经失效
}

int main(void)
{
	//test0();
	test1();

	return 0;
}
