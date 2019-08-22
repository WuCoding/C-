#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::for_each;
using std::remove_if;

class Number
{
	public:
		//构造函数
		Number(int data=0)
		: _data(data)
		{}

		//打印函数
		void display() const
		{
			cout<<_data<<" ";
		}
		
		//是否是偶数
		bool isEven() const
		{
			return !(_data%2);
		}

		//是否是素数
		bool isPrime() const
		{
			if(_data==1)
			{
				return false;
			}

			for(size_t idx=2;idx<=_data/2;++idx){
				if(!(_data%idx))
				{
					return false;
				}
			}
			return true;
		}
	private:
		//数据成员
		size_t _data;
};

int main(void)
{
	//创建自定义类型的vector容器
	vector<Number> numbers;
	//emplace_back在容器尾部添加一个元素，这个元素原地构造，
	//不需要触发复制构造函数，直接根据参数初始化临时对象的
	//成员
	
	//push_back在容器尾添加一个元素，如果添加的是一个匿名对
	//象则先调用传参构造函数创建一个匿名对象，再调用复制构造
	//函数创建一个容器中的元素，再调用析构函数，销毁匿名对象
	
	//相比之下emplace_back效率更高
	
	for(size_t idx=1;idx!=20;++idx){
		numbers.emplace_back(idx);
	}

	//将容器中的元素打印出来
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	//因为调用成员函数不像调用普通函数，需要默认传递对象地址作为this指针
	//所以在成员函数外加一个std::mem_fn()
	cout<<endl;
	//显示：1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

#if 0
	//remove_if不执行删除操作，只是将不是目标元素的元素往前移动
	auto it=remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isEven));
	//打印当前容器中的元素
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout<<endl;
	it->display();
	//可见容器中依然是19个元素，并没有将偶数删除，只是将非偶数的元素
	//往前移了，同时remove_if返回的是指向第一个无效元素的迭代器，所以
	//remove_if要与erase一起使用
	//显示：1 3 5 7 9 11 13 15 17 19 11 12 13 14 15 16 17 18 19
	//      11
#endif

	//remove_if和erase结合使用
	//erase参数范围左闭右开
	//删除容器中的偶数
	numbers.erase(remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isEven)),
		numbers.end());
	//打印容器中元素
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout<<endl;
	//显示：

	//删除容器中的素数
	numbers.erase(remove_if(numbers.begin(),numbers.end(),std::mem_fn(&Number::isPrime)),
			numbers.end());
	//打印容器中的元素
	for_each(numbers.begin(),numbers.end(),std::mem_fn(&Number::display));
	cout<<endl;

	return 0;
}



