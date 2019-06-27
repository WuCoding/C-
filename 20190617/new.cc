#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
//malloc和free库函数的使用
void test0()
{
	int *p1=(int*)malloc(sizeof(int));
	//malloc不进行清零
	::memset(p1,0,sizeof(int));
	*p1=10;
	printf("*p=%d\n",*p1);
	//释放掉malloc空间
	free(p1);
	//为数组申请malloc空间
	int *p2=(int*)malloc(sizeof(int)*10);
	//释放掉数组的malloc空间
	free(p2);
}
//new和delete表达式的使用
void test1()
{
	//申请了一个int空间并初始化为1
	int *p1=new int(1);
	cout<<"*p1="<<*p1<<endl;
	//释放掉该堆内存空间
	delete p1;
	//为数组申请空间
	int *p2=new int[10]();//加小括号有初始化，不加小括号无初始化
	//释放掉该堆空间
	delete [] p2;

}
int main(void)
{
	test0();
	test1();
	return 0;
}


	
