#include <string.h>

#include <iostream>
using std::cout;
using std::endl;
//自己创一个String字符串的类
class String
{
	public:
		//构造函数
		String()
		: _pstr(nullptr)
		{
			cout<<"String()"<<endl;
		}

		//传参构造函数
		String(const char* pstr)
		: _pstr(new char[strlen(pstr)+1]())//深拷贝
		{
			strcpy(_pstr,pstr);
			cout<<"String(const char* pstr)"<<endl;
		}

		//复制构造函数
		String(const String & rhs)
		: _pstr(new char[strlen(rhs._pstr)+1]())
		{
			strcpy(_pstr,rhs._pstr);
			cout<<"String(const String &)"<<endl;
		}

		//赋值运算符重构函数
		String & operator=(const String & rhs)
		{
			cout<<"String & operator=(const String&)"<<endl;
			//赋值运算符重构三部曲
			if(this!=&rhs){//防止自复制 a=a
				//销毁原有堆空间
				delete[] _pstr;
				//重新开辟堆空间
				_pstr=new char[strlen(rhs._pstr)+1]();
				//进行复制
				strcpy(_pstr,rhs._pstr);
			}
			return *this;
		}

		//下标运算符重载函数
		char & operator [](int idx)
		{
			if(idx>=0&&idx<strlen(_pstr)){
				return _pstr[idx];
			}else{
				cout<<" idx越界！"<<endl;
				static char nullchar='\0';
				return nullchar;
			}
		}

		//打印函数
		void print() const
		{
			if(_pstr!=nullptr){//如果_pstr不为空
				cout<<_pstr<<endl;
			}
		}

		//析构函数
		~String()
		{
			if(_pstr!=nullptr){//如果_pstr不为空
				delete [] _pstr;
			}
			cout<<"~String()"<<endl;
		}

		//获得字符串长度函数
		int size() const
		{
			return strlen(_pstr);
		}
	private:
		  char *_pstr;
};

int main(void)
{
	String s1;
	s1.print();
#if 0
	cout<<"1111"<<endl;
	int *p=nullptr;

	cout<<"p="<<p<<endl;
	cout<<"2222"<<endl;
#endif
	
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
	
	cout<<"下标访问运算符"<<endl;
	
	for(int idx=0;idx!=s4.size();++idx)
	{
		cout<<s4[idx]<<endl;
	}

	return 0;
}










