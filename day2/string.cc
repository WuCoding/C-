#include <string.h>

#include <string>
#include <iostream>
using std::cout;
using std::endl;

//C风格字符串
void test0()
{
	//位于/只读段/文字常量区/不可对pstr1和pstr2进行修改，所以要在前面加一个const否则编译不通
	const char *pstr1="hello";
	const char *pstr2="world";
	//在堆空间开辟一个字符串空间
	char *ptmp=new char[strlen(pstr1)+strlen(pstr2)+1]();//加小括号为了自动填0
	strcpy(ptmp,pstr1);
	strcat(ptmp,pstr2);
	cout<<"ptmp="<<ptmp<<endl;
	//释放堆空间内存
	delete [] ptmp;
}
//C++风格字符串
void test1()
{
	//把C风格字符串转换成C++风格的字符串
	std::string s1="hello";
	std::string s2="world";

	//字符串拼接
	cout<<"----------------字符串拼接--------------------"<<endl;
	std::string s3=s1+s2;
	cout<<"s3="<<s3<<endl;
	s3+="hello";
	cout<<"s3="<<s3<<endl;
	
	//获取字符串的长度
	cout<<"--------------获取字符串长度------------------"<<endl;
	cout<<"s3.size="<<s3.size()<<endl;
	cout<<"s3.length="<<s3.length()<<endl;

	//把C++风格字符串转换成C风格字符串
	cout<<"--------C++风格字符串转为C风格字符串----------"<<endl;
	const char *pstr=s3.c_str();
	const char *pstr2=s3.data();
	cout<<"s3.c_str()="<<s3.c_str()<<endl;
	cout<<"s3.data()="<<s3.data()<<endl;
	
	//遍历C++风格字符串的每个元素
	cout<<"--------遍历C++风格字符串的每个元素-----------"<<endl;
	for(size_t idx=0;idx!=s3.size();++idx)
	{
		cout<<"s3["<<idx<<"]="<<s3[idx]<<endl;
	}
	//注：&s3 代表的是std::string类型的对象的首地址，而不是字符串的首地址
	
	//C++字符串的尾加函数
	cout<<"-------------C++字符串尾加函数-----------------"<<endl;
	s3.append(3,'j');
	cout<<"s3="<<s3<<endl;
	s3.append(s1);
	cout<<"s3="<<s3<<endl;
	s3.append("wangdao");
	cout<<"s3="<<s3<<endl;
	s3.append("shenzhen",4);
	cout<<"s3="<<s3<<endl;

	//实现C++字符串查找元素
	cout<<"------------C++字符串的元素查找----------------"<<endl;
	size_t pos=s3.find("world");
	cout<<"pos of world in s3 is "<<pos<<endl;
	std::string s4=s3.substr(pos,5);
	cout<<"s3.substr(pos,5)="<<s4<<endl;
}
int main(void)
{
	cout<<"------------------------------test0--------------------------------"<<endl;
	test0();
	cout<<"-------------------------------test1-------------------------------"<<endl;
	test1();
	return 0;
}


