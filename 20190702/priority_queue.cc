#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;

//外部排序

//内部排序（八大排序）
//    >插入排序
//    >希尔排序
//    >选择排序
//    >冒泡排序
//    >快排
//    >堆排
//    >归并排序
//    >基数排序

//    >（计数排序）

//--------------------------------priority(优先级队列)-------------------------------
void test0()
{
	//优先级队列的底层实现：堆排序
	//    >小于符号，得到的是一个大顶堆
	//    >大于符号，得到的是一个小顶堆
	//每次操作的堆顶的元素，将堆顶元素作为左操作数，
	//与新来的元素进行比较，如果返回值为true，则用
	//新来的元素替换堆顶的元素
	
	vector<int> vec{5,1,2,6,9,7,3,4,8};
#if 0
	priority_queue<int> numbers(vec.begin(),vec.end());
	//显示：9 8 7 6 5 4 3 2 1
#endif

#if 0
	priority_queue<int> numbers;
	//显示：当前队列中优先级最高的元素是：5
	//      当前队列中优先级最高的元素是：5
	//      当前队列中优先级最高的元素是：5
	//      当前队列中优先级最高的元素是：6
	//      当前队列中优先级最高的元素是：9
	//      当前队列中优先级最高的元素是：9
	//      当前队列中优先级最高的元素是：9
	//      当前队列中优先级最高的元素是：9
	//      当前队列中优先级最高的元素是：9
	//9 8 7 6 5 4 3 2 1
#endif

#if 1
	priority_queue<int,vector<int>,std::greater<int>> numbers;
	//显示：当前队列中优先级最高的元素是：5
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//      当前队列中优先级最高的元素是：1
	//1 2 3 4 5 6 7 8 9
#endif

#if 1
	for(auto it=vec.begin();it!=vec.end();++it)
	{
		numbers.push(*it);
		cout<<"当前队列中优先级最高的元素是："<<numbers.top()<<endl;
	}
#endif
	while(!numbers.empty())
	{
		cout<<numbers.top()<<" ";
		numbers.pop();
	}
	cout<<endl;
}

int main(void)
{
	test0();

	return 0;
}
