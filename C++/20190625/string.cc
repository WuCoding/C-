#include <stdio.h>

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main(void)
{
	int a=1;//用来看栈空间地址大小
	int *p=new int(10);//用来看堆空间地址大小
	string s1="hello";
	string s2="helloworldaaaaa";
	string s3="helloworldaaaaaa";

	string s4=s1;
	string s5=s3;
	//所有string类型的对象大小都为32
	cout<<"sizeof(s1)="<<sizeof(s1)<<endl;
	cout<<"sizeof(s2)="<<sizeof(s2)<<endl;
	cout<<"sizeof(s3)="<<sizeof(s3)<<endl;
	cout<<"sizeof(s4)="<<sizeof(s4)<<endl;
	//短字符串在栈空间，长字符串在堆空间，且复制时都是深拷贝
	//s1,s2,s4地址都在栈空间，且s1和s4地址不同
	cout<<"s1="<<s1<<endl;
	//打印地址，因为取地址s1是string对象的地址而不是字符串开头的地址，要获得字符串，需要用c_str()
	printf("s1's address is %p\n",s1.c_str());
	cout<<"s4="<<s4<<endl;
	printf("s4's address is %p\n",s4.c_str());
	cout<<"s2="<<s2<<endl;
	printf("s2's address is %p\n",s2.c_str());
	//s3,s5地址在堆空间，且s3和s5的地址也不同，属于深拷贝
	cout<<"s3="<<s3<<endl;
	printf("s3's address is %p\n",s3.c_str());
	cout<<"s5="<<s5<<endl;
	printf("s5's address is %p\n",s5.c_str());
	//显示栈空间地址
	printf("&a=%p\n",&a);
	//显示堆空间地址
	printf("p=%p\n",p);

	return 0;
}

