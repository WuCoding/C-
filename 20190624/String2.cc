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





	private:
		  char *_pstr;
};
