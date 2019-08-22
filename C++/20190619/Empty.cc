#include <iostream>
using std::cout;
using std::endl;
//空的类，没有数据成员
class Empty
{};

int main(void)
{
	Empty e1;
	Empty e2;
	
	//虽然两个对象的数据成员都为空，但是两个对象地址不同
	cout<<"&e1="<<&e1<<endl
		<<"&e2="<<&e2<<endl;
	//两个对象的大小也并不为0，而是为1
	cout<<"sizeof(e1)="<<sizeof(e1)<<endl
		<<"sizeof(e2)="<<sizeof(e2)<<endl;
	return 0;
}
