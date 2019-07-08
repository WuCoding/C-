#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <fstream>
using std::cout;
using std::endl;
using std::copy;
using std::vector;
using std::ofstream;
using std::ostream_iterator;

int main(void)
{
	//创建一个vector容器
	vector<int> numbers{1,2,3,4,5};
	//打印容器中的元素信息
	for(auto it=numbers.begin();it!=numbers.end();++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;

	//把输出流看成一个容器
	
	//创建一个输出流迭代器（迭代器适配器）
	//输出流迭代器绑定到cout上（标准输出流）
	ostream_iterator<int> osi(cout," ");
	//copy算法，将vector容器中的元素拷贝到输出流容器中
	copy(numbers.begin(),numbers.end(),osi);
	cout<<endl;

	//创建一个文件输出流，向文件中输出数据
	ofstream ofs("test.txt");
	if(!ofs){//文件输出流绑定失败
		cout<<"ofstream open file error!"<<endl;
		return -1;
	}
	//输出流迭代器绑定到ofs上（文件输出流）
	ostream_iterator<int> ofsi(ofs,",");
	//将vector容器中的元素，拷贝到输出流容器中
	copy(numbers.begin(),numbers.end(),ofsi);

	return 0;
}

