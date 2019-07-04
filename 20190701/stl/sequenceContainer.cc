#include <iostream>
#include <vector>
#include <list>
#include <deque>
using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::deque;


/*
class Example
{
	public:
		int _data;
		class Pimpl;//类中定义的类
};
Example::_data;
Example::Pimple; 通过类名来访问类内成员
*/


//函数模板
template <class Container>
void display(const Container &c)
{
	typename Container::const_iterator it=c.begin();
	//typename关键字告诉编译器const_iterator是类型名，不然编译器会报错
	//因为参数c被const限定，所以迭代器要用const_iterator
	while(it!=c.end())//迭代器end()指向的是容器最后一个元素的下一位置
	{		//而不是最后一个元素
		//解引用迭代器，表示的是迭代器指向的容器中的元素
		cout<<*it<<" ";
		//迭代器指向后一个元素
		++it;
	}
	cout<<endl;
}

void test0()//该测试函数，测试vector容器特性
{
	cout<<">>> test vector:"<<endl;
	//容器第一种初始化，只有一个参数
	//    >vector<int> numbers(10); 
	//    >该容器中含有10个值为0的元素
	//容器第二种初始化，两个参数
	//    >vector<int> numbers(10,1); 
	//    >该容器含有10个值为1的元素
	//容器第三种初始化
	//    >int arr[5]={1,2,3,4,5};
	//    >vector<int> numbers(arr,arr+5);    
	//    >用两个指针将容器初始化，arr+5是指向最后一个元素的后一位置，
	//    >而不是指向最后一个元素
	//容器第四种初始化
	      vector<int> numbers{1,2,3,4,5};
	//    >动态数组
	display(numbers);
	//打印numbers容器空间大小
	cout<<">> number's capacity="<<numbers.capacity()<<endl;
	//打印numbers容器的大小
	cout<<">> sizeof(numbers)="<<sizeof(numbers)<<endl;

	//为什么vector没有提供push_front/pop_front?
	//    >vector若提供了头部删除和头部添加特性，那么每次头部添加，
	//    >就会造成容器中所有元素往后移一位，再在头部添加新的元素，
	//    >如果头部删除，则将头部元素删除后，再将后面的元素，整体往
	//    >前移一位，两种操作的时间复杂度为0(N)
	//所以vector不提倡在头部添加或者删除元素
	
	//vector数据结构就是栈
	//numbers.push_back(11); 压栈
	//numbers.pop_back();  出栈
	
	cout<<">> numbers[2]="<<numbers[2]<<endl;

	cout<<">> test insert:"<<endl;
	cout<<">> numbers's capacity="<<numbers.capacity()<<endl;

	//在容器中插入元素insert，vector的insert操作时间复杂度为0(N)
	//vector<int>::iterator it=numbers.begin();  迭代器it指向容器第一个元素
	auto it=numbers.begin(); //或者用auto关键字，auto关键字具有自动推导的功能
	//将迭代器指向下一个元素
	++it;
	//输出该迭代器指向的元素的值
	cout<<"*it="<<*it<<endl;
	auto it2=numbers.insert(it,22);
	//在it迭代器指向的位置处插入22，因为插入过程可能会因原有空间不足而重新开辟
	//空间，导致it迭代器仍然指向原有已经无效的地址，所以必须用一个新的迭代器it2
	//来重新获取新的空间的该元素的地址
	cout<<">> *it="<<*it<<endl;//无效值，迭代器失效了
	cout<<">> *it2="<<*it2<<endl;
	//打印容器中的元素信息
	display(numbers);

	//在迭代器it2的位置插入一个新的元素3.33
	numbers.insert(it2,3.33);
	//打印容器中元素的信息
	display(numbers);
	cout<<"*it2="<<*it2<<endl;

	//迭代器it重新获取容器首元素地址
	it=numbers.begin();
	//另一种插入方式，将另一个容器的元素，插入到要插入的容器中
	vector<int> numbers2{41,42,43,44};
	numbers.insert(it,numbers2.begin(),numbers2.end());
	//将插入位置，传入的范围起点（用迭代器表示），传入的范围终点（用迭代器表示）
	//传入insert成员函数中
	display(numbers); //打印容器中的元素信息


	//如果要收回多余的空间，可以使用shrink_to_fit，将没有用到的空间释放掉
	numbers.shrink_to_fit();
	cout<<">> numbers's capacity="<<numbers.capacity()<<endl;

	//清空容器中的元素
	cout<<">> clear elements test:"<<endl;
	numbers.clear(); //对vector来说，清空元素之后，没有回收空间
	display(numbers);
	//将多余的空间收回
	numbers.shrink_to_fit();
	cout<<">> numbers's capacity="<<numbers.capacity()<<endl;
}

void test1() //该测试函数，测试deque容器属性，deque为双端队列，可在头尾插入和删除
{
	cout<<endl<<">>> test deque:"<<endl;
	//第一种初始化方式，只有一个参数
	//    >deque<int> numbers(10);
	//    >该容器中有10个值为0的元素
	//第二种初始化方式，有两个参数
	//    >deque<int> numbers(10,2);
	//    >该容器中有10个值为2的元素
	//第三种初始化方式
	//    >int arr[5]={1,2,3,4,5};
	//    >deque<int> numbers(arr,arr+5); 
	//    >arr+5指向的是最后一个元素的下一个位置，而不是最后一个元素
	//第四种初始化方式
	deque<int> numbers{1,2,3,4,5};
	//打印容器中的元素信息
	display(numbers);
	//cout<<">> numbers's capacity="<<numbers.capacity()<<endl;
	//这句语句错误，因为deque容器没有capacity()方法，这与deque容器的底层实现方式
	//有关，deque的底层是由多个不相连的区域组成，而每个独自的区域在内存上是连续的
	
	//在容器尾部插入元素
	numbers.push_back(21);
	//在容器头部插入元素
	numbers.push_front(31);
	//打印容器的元素信息
	display(numbers);
	//从容器头部删除元素
	numbers.pop_front();
	//打印容器中元素信息
	display(numbers);

	cout<<"numbers[2]="<<numbers[2]<<endl;

	//进行deque容器的插入测试insert，deque的insert操作时间复杂度为0(N)
	cout<<">> test insert:"<<endl;
	//auto关键字具有自动推导功能
	auto it=numbers.begin();//将迭代器指向容器首元素
	//将迭代器进行偏移，到下一个元素
	++it;
	//将迭代器it指向的元素打印出来
	cout<<"*it="<<*it<<endl;
	//进行插入操作
	auto it2=numbers.insert(it,22);//必须重新获取迭代器
	cout<<"*it="<<*it<<endl;//无效值，该迭代器已经失效
	cout<<"*it2="<<*it2<<endl;
	//打印容器中元素信息
	display(numbers);

	//执行插入操作
	numbers.insert(it2,3.33);
	//打印容器中元素信息
	display(numbers);
	cout<<"*it2="<<*it2<<endl;

	//迭代器重新获得容器首元素地址
	it=numbers.begin();
	//将一个vector容器的元素插入到另一个deque容器中
	vector<int> numbers2{41,42,43,44};
	//插入操作
	numbers.insert(it,numbers2.begin(),numbers2.end());
	//将插入位置，插入容器范围头部（用迭代器表示），插入容器范围尾部（用迭代器表示）
	//传入insert()成员函数中
	
	//打印容器中的元素信息
	display(numbers);

	//对容器清空测试clear()
	cout<<">> clear elements test:"<<endl;
	//将容器清空
	numbers.clear();
	//打印容器中的元素信息
	display(numbers);
	//将容器未用到的空间释放
	numbers.shrink_to_fit();
}

void test2()//该测试函数，用来测试list容器的特性，list为双向链表，在底层实现是通过环形双向链表
{
	cout<<">>> test list:"<<endl;
	//第一种初始化方式，一个参数
	//    >list<int> numbers(10);
	//    >该容器中含有10个值为0的元素
	//第二种初始化方式，两个参数
	//    >list<int> numbers(10,2);
	//    >此时容器中含有10个值为2的元素
	//第三种初始化方式
	//    >int arr[5]={1,2,3,4,5};
	//    >list<int> numbers(arr,arr+5);
	//    >注意这里arr+5指向的是最后一个元素的下一位置，而不是最后一个元素
	//第四种初始化方式
	list<int> numbers{1,2,3,4,5};
	//打印容器中元素信息
	display(numbers);
	//cout<<">> numbers's capacity="<<numbers.capacity()<<endl;
	//该语句执行失败，因为list中没有capacity()方法，因为在底层实现上是一个环形链表
	//不需要提前开辟空间
	
	//在尾部插入元素，时间复杂度为0(1)
	numbers.push_back(21);
	//在头部插入元素
	numbers.push_front(31);
	//打印容器中的元素信息
	display(numbers);

	//在头部删除一个元素
	numbers.pop_front();
	//打印容器中的元素信息
	display(numbers);

	//cout<<"numbers[2]="<<numbers[2]<<endl;
	//这条语句执行错误，因为list不支持下标访问，只支持双向访问
	
	//测试list插入测试insert,list的insert操作时间复杂度为0(1)，因为底层实现为环形链表
	cout<<">> test insert:"<<endl;
	//auto关键字具有自动推导的功能
	auto it=numbers.begin();
	//将迭代器指针进行偏移，指向下一个元素
	++it;
	//打印迭代器it指向的元素
	cout<<"*it="<<*it<<endl;
	//执行插入操作
	auto it2=numbers.insert(it,22);//用一个新的迭代器来接收新元素的位置
	cout<<"*it="<<*it<<endl;
	cout<<"*it2="<<*it2<<endl;
	//打印函数信息
	display(numbers);

	//执行插入操作
	numbers.insert(it2,3.33);
	//打印容器中的元素信息
	display(numbers);
	cout<<"*it2="<<*it2<<endl;

	//将迭代器it指向容器首元素
	it=numbers.begin();
	//将一个vector容器中的元素插入到list容器中
	vector<int> numbers2{41,42,43,44};
	//执行插入操作
	numbers.insert(it,numbers2.begin(),numbers2.end());
	//将插入位置，插入元素范围头部（用迭代器表示），插入元素范围尾部（用迭代器表示）
	//传入到insert()成员函数中

	//打印容器中元素信息
	display(numbers);

	//将容器中的元素清空
	cout<<"clear elements test:"<<endl;
	//执行清空元素操作
	numbers.clear();
	//打印容器中元素信息
	display(numbers);
}

int main(void)
{
	test0();
	test1();
	test2();

	return 0;
}
	




