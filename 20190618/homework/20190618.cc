//C++内存布局分为几个区域，各自具备什么特点？
//内存区域 0~3 G为用户态程序空间，3~4 G为内核态
//由下到上，以此为：
//只读区：文字常量区，程序代码区，字符串常量和函数代码存储在这里
//数据段：全局/静态区 全局变量 静态变量存储在这里
//堆：堆由下而上进行扩展 存储堆对象
//栈：栈由上而下进行扩展 存储栈对象
//
//
//当定义类时，编译器会为类自动生成哪些函数？这些函数各自有什么特点？
//会默认生成：默认构造函数，默认析构函数，默认赋值运算符函数，默认赋值构造函数
//
//什么是浅拷贝，什么是深拷贝？
//浅拷贝：
//当一个堆对象浅拷贝给一个指针时，只是将该堆对象的首地址赋值给该指针，两个堆指针指向的是同一个堆内存
//深拷贝：
//当一个堆对象深拷贝给一个指针时，该指针重新在堆内存上开辟一块空间，在这个新空间将原堆内存的数据拷贝过来，深拷贝的两个堆指针指向两个堆空间，这两个堆空间内容相同
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;
class String
{
	public:
		//构造函数
		String()
		: _pstr(new char[20]())
		{
			cout<<"String()"<<endl;
		}
		String(const char *pstr)
		: _pstr(new char[strlen(pstr)+1]())
		{
			strcpy(_pstr,pstr);
			cout<<"String(const char *pstr)"<<endl;
		}
		String(const String &rhs)
		: _pstr(new char[strlen(rhs._pstr)+1]())
		{
			strcpy(_pstr,rhs._pstr);
			cout<<"String(const String &rhs)"<<endl;
		}
		String & operator=(const String &rhs)
		{
			//三部曲
			if(&rhs==this)//防止自复制
			{
				return *this;
			}
			delete [] this->_pstr;
			this->_pstr=new char[strlen(rhs._pstr)+1];
			strcpy(this->_pstr,rhs._pstr);
			return *this;
		}
		//析构函数
		~String()
		{
			if(this->_pstr!=nullptr)
			{
				delete [] this->_pstr;
				this->_pstr=nullptr;
			}
		}
		void print()
		{
			cout<<"string="<<this->_pstr<<endl;
		}
	private:
		char *_pstr;
};

int main(void)
{
	String str1;
	str1.print();

	String str2="Hello,world";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4=str3;
	str4.print();

	str4=str2;
	str4.print();

	return 0;
}
