#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

//对于基类的复制构造函数和赋值运算符重载函数，派生类都没有继承

//当派生类与派生类对象进行复制控制操作时：
//1. 如果派生类没有显式定义复制控制函数，则会自动调用基类的相应复制控制函数
//2. 如果是派生类有显式定义复制控制函数，基类也有显式定义复制控制函数，则基类部分不必再自动调用
//相应的复制控制函数，需要手动调用

//基类
class Base
{
	public:
		//传参构造函数
		Base(const char *data)
		: _data(new char[strlen(data)+1]())
		{
			cout<<"Base(const char *data)"<<endl;
			strcpy(_data,data);
		}

		//复制构造函数
		Base(const Base & rhs)
		: _data(new char[strlen(rhs._data)+1]())
		{
			strcpy(_data,rhs._data);
			cout<<"Base(const Base &)"<<endl;
		}

		//赋值运算符重载函数
		Base & operator=(const Base & rhs)
		{
			cout<<"Base & operator=(const Base &)"<<endl;
			//三部曲
			if(this!=&rhs){ //防止自复制
				//释放之前空间
				delete []_data;
				//开辟新空间
				_data=new char[strlen(rhs._data)+1]();
				//复制
				strcpy(_data,rhs._data);
			}
			return *this;
		}

		//析构函数
		~Base()
		{
			cout<<"~Base()"<<endl;
			delete []_data;
		}

		//获得private数据成员函数
		const char * data() const
		{
			return _data;
		}

	private:
		  //数据成员
		  char *_data;
};

//派生类
class Derived
: public Base  //以public方式继承
{
	public:
		//传参构造函数
		Derived(const char *data,const char *data2)
		: Base(data) //主动调用Base类的构造函数
		, _data(new char[strlen(data2)+1]())
		{
			cout<<"Derived(const char *,const char *)"<<endl;
			strcpy(_data2,data2);
		}

		//复制构造函数
		Derived(const Derived & rhs)
		: Base(rhs)  //主动调用Base类的构造函数
		, _data2(new char[strlen(rhs._data2)+1]())
		{
			cout<<"Derived(const Derived &)"<<endl;
			strcpy(_data2,rhs._data2);
		}

		//赋值运算符重构函数
		Derived & operator=(const Derived & rhs)
		{
			cout<<"Derived & operator=(const Derived &)"<<endl;
			if(this!=&rhs){ //防止自复制
				//这里显式调用基类的赋值运算符函数
				Base::operator=(rhs);
				//释放掉之前的空间
				delete []_data2;
				//重新开辟新的空间
				_data2=new char[strlen(rhs._data2)+1]();
				//进行复制
				strcpy(_data2,rhs._data2);
			}
			return *this;
		}

		//析构函数
		~Derived()
		{
			cout<<"~Derived()"<<endl;
		}

		//输出运算符重载函数的友元声明
		friend std::ostream & operator<<(std::ostream & os,const Derived & rhs);

	private:
		//数据成员
		char *_data2;
};
//Deived类的输出运算符重构函数实现
std::ostream & operator<<(std::ostream & os,const Derived & rhs)
{
	os<<rhs.data()<<","<<rhs._data2;
	return os;
}

int main(void)
{
	//传参构造
	Derived d1("hello","world");
	cout<<"d1="<<d1<<endl;
	//复制构造
	Derived d2=d1;
	cout<<"d2="<<d2<<endl;

	Derived d3("guangdong","shenzhen");
	cout<<"d3="<<d3<<endl;
	//赋值操作
	d3=d1;
	cout<<"d3="<<d3<<endl;

	return 0;
}





































