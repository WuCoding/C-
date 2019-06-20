#include "Computer2.h"

#include <iostream>
using std::cout;
using std::endl;

void display()
{
	int a=100;
	cout<<"display()"<<endl;
	cout<<"a="<<a<<endl;
}

int main(void)
{
	//无论是普通定义的函数，还是类的成员函数都是指令，存在于程序代码区，函数名是指令段的入口
	display();

	Computer pc1;
	pc1.setBrand("Thinkpad");//这里是Computer::serBrand()函数段的入口
	pc1.setPrice(8888);
	pc1.print();

	cout<<"sizeof(Computer)="<<sizeof(Computer)<<endl;
	//结果打印出32
	//原因为：
	//为了数据成员的完整性，在存储中每一项数据成员时都分配8的整数倍的空间
	//char _brand[20]该数据成员占20字节，实际分配了24个字节
	//double _price该数据成员占8字节，实际分配8字节
	//结果为8+24=32
	//因为是64位操作系统，为数据完整性分配8的整数倍
	//32位操作系统，分配给每一个数据成员的空间为4的整数倍
}
