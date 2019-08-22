#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//含参构造函数
		Base(const char *data)
		: _data(new char[strlen(data)+1]())//深拷贝
		{
			cout<<"Base(const char *data)"<<endl;
			strcpy(_data,data);
		}

		//复制构造函数
		Base(const Base & rhs)
		: _data(new char[strlen(rhs._data)+1]())
		{
			cout<<"Base(const Base &)"<<endl;
			strcpy(_data,rhs._data);
		}

		//赋值运算符重构函数
		Base & operator=(const Base & rhs)
		{
			cout<<"Base & operator=(const Base &)"<<endl;
			//三部曲
			if(this!=&rhs){//防止自复制
				//释放原有空间
				delete []_data;
				//开辟新的空间
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

		//获得数据成员_data
		const char* data() const
		{
			return _data;
		}

	private:
		//数据成员
		char * _data;
};


//派生类
class Derived
: public Base //以public方式继承
{
	public:
		//构造函数
		Derived(const char *data)
		: Base(data)  //调用Base类构造函数
		{
			cout<<"Derived()"<<endl;
		}

		//析构函数
		~Derived()
		{
			cout<<"~Derived()"<<endl;
		}
};

//派生类输出运算符<<重载函数实现
//因为该重载函数通过Base类的public成员data()来获得private数据成员，所以不需要作为友元函数来访问
//类的私有成员
std::ostream & operator<<(std::ostream & os,const Derived & rhs)
{
	os<<rhs.data();
	return os;
}

int main(void)
{
	//传参初始化
	Derived d1("hello");
	cout<<"d1="<<d1<<endl;

	//复制初始化
	Derived d2=d1;
	cout<<"d2="<<d2<<endl;

	Derived d3("world");
	cout<<"d3="<<d3<<endl;

	//赋值运算
	d3=d1;
	cout<<"d3="<<d3<<endl;

	return 0;
}
	








































