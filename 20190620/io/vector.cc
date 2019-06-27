#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
//显示一个容器当前的元素数量和当前容量
void printVectorCapacity(const vector<int> &c)
{
	cout<<"c's size="<<c.size()<<endl;
	cout<<"c's capacity="<<c.capacity()<<endl;
}

int main(void)
{
	int arr[10];//静态数组
	//动态数组
	//策略：当数组中的size()==capacity()，并且此时还要添加新的元素时，需要进行动态扩容。
	//先去申请2*capacity()的空间，然后把原来空间中的元素全部复制到新的空间中，然后去释放
	//原来的空间的数据，最后再添加新的元素
	vector<int> numbers;
	//提前扩充空间容量为100
	//numbers.reserve(100);
	//显示该容器的当前元素数量和容量
	printVectorCapacity(numbers);

	numbers.push_back(1);
	printVectorCapacity(numbers);
	numbers.push_back(2);
	printVectorCapacity(numbers);
	numbers.push_back(3);
	printVectorCapacity(numbers);
	numbers.push_back(4);
	printVectorCapacity(numbers);
	numbers.push_back(5);
	printVectorCapacity(numbers);
	numbers.push_back(6);
	printVectorCapacity(numbers);
	numbers.push_back(7);
	printVectorCapacity(numbers);
	numbers.push_back(8);
	printVectorCapacity(numbers);
	numbers.push_back(9);
	printVectorCapacity(numbers);
	//从容器中删除元素
	numbers.pop_back();//删除的是尾部元素，即后插入的元素，此处删除的是9
	//遍历容器中的元素方式1：
	for(size_t idx=0;idx!=numbers.size();++idx)
	{
		cout<<numbers[idx]<<" ";
	}
	cout<<endl;
	//遍历容器中的元素方式2：c++11
	for(auto &number:numbers)
	{
		cout<<number<<" ";
	}
	cout<<endl;
	//遍历容器中的元素方式3：迭代器访问
	auto iter=numbers.begin();
	while(iter!=numbers.end())
	{
		cout<<*iter<<" ";
		++iter;
	}
	cout<<endl;

	return 0;
}
	
	





















	for(auto &element:numbers)
	{
		cout<<element<<" ";
	}
	cout<<endl;
	return 0;
}
	


























