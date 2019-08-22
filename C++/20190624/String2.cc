#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class String
{
	public:
		//无参构造函数
		String()
		: _pstr(new char[1]())
		{
			cout<<"String()"<<endl;
		}

		//传字符串构造函数
		String(const char * pstr)
		: _pstr(new char[strlen(pstr)+1]())
		{
			strcpy(_pstr,pstr);
			cout<<"String(const char * pstr)"<<endl;
		}

		//复制构造函数
		String(const String & rhs)
		: _pstr(new char[strlen(rhs._pstr)+1]())
		{
			cout<<"String(const String &)"<<endl;
			strcpy(_pstr,rhs._pstr);
		}

		//赋值运算符重构函数
		String & operator=(const String & rhs)
		{
			cout<<"String & operator=(const String&)"<<endl;
			//三部曲
			if(this!=&rhs){//如果两个对象不是同一个
				//释放旧空间
				delete [] _pstr;
				//创建新空间
				_pstr=new char[strlen(rhs._pstr)+1]();
				//进行复制
				strcpy(_pstr,rhs._pstr);
			}
			//返回该对象
			return *this;
		}

		//打印函数
		void print() const
		{
			cout<<_pstr<<endl;
		}

		//析构函数，释放字符串的堆空间
		~String()
		{
			delete [] _pstr;
			cout<<"~String()"<<endl;
		}
	private:
		  char *_pstr;
};

int main(void)
{
	String s1;
	s1.print();

	String s2="hello";
	cout<<"s2=";
	s2.print();

	String s3=s2;
	cout<<"s3=";
	s3.print();

	String s4="world";
	s4=s2;
	cout<<"s4=";
	s4.print();

#if 0
	cout<<"1111"<<endl;
	int *p=nullptr;

	cout<<"p="<<p<<endl;
	cout<<"2222"<<endl;
#endif
	return 0;
}
