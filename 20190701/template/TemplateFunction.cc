#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

//            实例化
//函数模板------------------>模板函数
//          模板参数推导

//本来是没有某个函数的定义的，但当执行这个函数时，会自动生成该函数的代码
//然后执行该函数的代码，模板就是一个代码生成器

//通用版本
template <class T>
T add(T x,T y);//这里是函数模板的声明

//函数模板与函数模板之间可以重载
template <class T>
T add(T x,T y,T z)
{
	cout<<"T add(T,T,T)"<<endl;
	return x+y+z;
}


//函数模板与普通函数可以重载，普通函数优先于函数模板的执行
#if 0
int add(int x,int y)
{
	cout<<"int add(int,int)"<<endl;
	return x+y;
}
#endif

//参数为多个类型的函数模板
#if 0
template <class T1,class T2>
T1 add(T1 x,T2 y)
{
	return x+y;
}
#endif

//模板的特化 （specialization）
//不能单独存在
//add函数模板的char类型的特化
template<>
const char* add<const char*>(const char *p1,const char *p2)
{
	int len=strlen(p1)+strlen(p2)+1;
	char *tmp=new char[len]();
	strcpy(tmp,p1);
	strcat(tmp,p2);
	return tmp;
}

//模板的偏特化 （部分参数指定特殊的类型）
//没写出模板的偏特化例子，浩哥说不需要掌握

int main(void)
{
	int x1=3,x2=4;
	double y1=1.11,y2=2.22,y3=3.33;
	char c1='a',c2=2;
	const char *p1="hello";
	const char *p2="world";

	//隐式实例化，没有直接给出参数类型，而是由编译器通过给出的系数类型，
	//来推测要生成的函数代码
	cout<<"add(x1,x2)="<<add(x1,x2)<<endl;//如果该语句执行时定义了int add(int,int)函数
					      //则会调用该函数，而不是函数模板
	//显式实例化，直接给出函数的参数的类型
	cout<<"add(y1,y2)="<<add<double>(y1,y2)<<endl;
	cout<<"add(c1,c2)="<<add(c1,c2)<<endl;
	//函数模板的重载
	cout<<"add(y1,y2,y3)="<<add(y1,y2,y3)<<endl;

	//如果没有定义多个类型的函数模板，也没有定义int add(int,int)函数
	//cout<<"add(x1,y1)="<<add(x1,y1)<<endl;
	//该语句将会执行出错
	
	cout<<"add(p1,p2)="<<add(p1,p2)<<endl;
	
	return 0;
}

//函数模板的实现
template <class T>
T add(T x,T y)
{
	cout<<"T add(T,T)"<<endl;
	return x+y;
}








































