#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::copy;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;

int main(void)
{
	cout<<"pls input valid integer!"<<endl;
	//输入迭代器
	istream_iterator<int> isi(cin); 
	//这条语句执行时，便开始等待输入端输入，相当于cin>>number;只有
	//输入数据之后才能接着往下执行
	vector<int> numbers;
	cout<<"numbers's size="<<numbers.size()<<endl;
	cout<<"numbers's capacity="<<numbers.capacity()<<endl;

	//copy(isi,istream_iterator<int>(),numbers.begin());
	//第一个参数为要输入范围的头迭代器，第二个为要输入范围的尾迭代器
	//在这里是内定的输入迭代器结束标志，第三个参数为要插入的位置
	//注意：
	//    >这里会报错，因为numbers.begin()要此时存在元素，不然容器
	//    >capacity为0，直接进行添加就会访问越界
	
	//numbers.push_back(number);  执行此句时会进行动态扩容
	
	//要插入新元素时，要使用插入迭代器，插入迭代器的底层实现是push_back()
	copy(isi,istream_iterator<int>(),std::back_inserter(numbers));
	//第二个参数为输入结束在输入端键入Ctrl+D表示输入结束

	//用输出迭代器来打印
	copy(numbers.begin(),numbers.end(),ostream_iterator<int>(cout," "));

	return 0;
}
