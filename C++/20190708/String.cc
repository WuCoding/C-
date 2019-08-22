#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

class String
{
	public:
		//无参构造函数
		String()
		: _pstr(nullptr)
		{
			cout<<"String()"<<endl;
		}

		//传参构造函数
		String(const char *pstr)
		: _pstr(new char[strlen(pstr)+1]())
		{
			strcpy(_pstr,pstr);
			cout<<"String(const char *pstr)"<<endl;
		}

		//复制构造函数
		String(const String &rhs) //const & 该引用传左右值都可以
		: _pstr(new char[strlen(rhs._pstr)+1]())
		{
			cout<<"String(const String &)"<<endl;
			strcpy(_pstr,rhs._pstr);
		}

		//赋值运算符重载函数
		String & operator=(const String &rhs)
		{
			cout<<"String & operator=(const String&)"<<endl;
			if(this!=&rhs){//防止自复制
				//三部曲
				delete []_pstr;

				_pstr=new char[strlen(rhs._pstr)+1]();
				strcpy(_pstr,rhs._pstr);
			}
			return *this;
		}

#if 1
		//移动构造函数，&& 右值引用，传左值对象将会报错
		String(String && rhs)
		: _pstr(rhs._pstr)  //_pstr字符指针，浅拷贝
		{
			//将原来的右值对象指针置为nullptr，这样就完成了
			//移动，而不是复制
			rhs._pstr=nullptr;
			cout<<"String(String &&)"<<endl;		
		}
#endif
		//移动赋值函数
		String & operator=(String && rhs)
		{
			cout<<"String & operator=(String&&)"<<endl;
			if(this!=&rhs){//防止自复制
				//将原来的空间释放
				delete [] _pstr;
				//将地址进行传递
				_pstr=rhs._pstr;
				//将右值的指针置为nullptr，完成转移
				rhs._pstr=nullptr;
			}
			return *this;
		}

		//下标访问运算符重载函数
		char & operator[](int idx)
		{
			if((idx>=0)&&(idx<strlen(_pstr))){
				//下标没有越界
				return _pstr[idx];
			}else{
				//下标越界
				cout<<"下标越界！"<<endl;
				static char nullchar='\0';
				return nullchar;
			}
		}

		//打印函数
		void print() const
		{
			if(_pstr){//指针不为空
				cout<<_pstr<<endl;
			}
		}

		//析构函数
		~String()
		{
			if(_pstr){//指针不为空
				delete [] _pstr;
				cout<<"~String()"<<endl;
			}
		}
		
		//获得字符串长度
		int size() const
		{
			return strlen(_pstr);
		}

		//友元函数声明
		//输出运算符重载函数
		friend std::ostream & operator<<(std::ostream &os,const String &rhs);	
	private:
		//数据成员
		char * _pstr;
};


//输出运算符重载函数的实现
std::ostream & operator<<(std::ostream &os,const String &rhs)
{
	os<<rhs._pstr;
	return os;
}

int test0()
{
	vector<String> vec;
	vec.push_back("hello,world");//临时对象，右值
	//显示：String(const char *pstr)
	//	String(String &&)

	vec[0].print();
	//显示：hello,world

	String s("wangdao");//左值
	//显示：String(const char *pstr)
	//	String(const String &)????????????????????????????
	
	vec.push_back(s);
	//显示：String(const String &)

	return 0;
	//显示：~String()
	//	~String()
	//	~String()
	//	~String()
}

int test1()
{
	String s1="hello";//s1为左值
	//显示：String(const char *pstr)
	//	String(String &&)
	cout<<"s1="<<s1<<endl;
	//显示：s1=hello

	String s2("world");
	//显示：String(const char *pstr)
	cout<<"s2="<<s2<<endl;
	//显示：s2=world

	//右值赋值
	s2=String("wangdao");
	//显示：String(const char *pstr)
	//	String & operator=(String&&)
	cout<<"s2="<<s2<<endl;
	//显示：s2=wangdao
	
	//左值赋值
	s2=s1;
	//显示：String & operator=(const String&)
	cout<<"s2="<<s2<<endl;
	//显示：s2=hello
	
	//将一个左值显式的转换为右值
	s2=std::move(s1);
	//显示：String & operator=(String &&)
	cout<<"s2="<<s2<<endl;
	//显示：s2=hello
	//cout<<"s1="<<s1<<endl;//s1本身的内容已经被转移走了
	//显示：s1=                  什么也不显示，而且程序崩溃

	cout<<"---------------------"<<endl;
	s1=std::move(s1);
	//显示：String &operator=(String&&)
	
	vector<String> vec;
	vec.push_back(std::move(s2));
	//显示：String(String &&)
	
	return 0;
	//显示：~String()
}

#if 0

//全局对象
String s1("hello");
//显示：String(const char *pstr)

String getString()
{
	String s("wangdao");//s是局部对象，马上就要销毁
	//显示：String(const char *pstr)

	//类中定义了具有移动语义函数，
	//函数返回值是对象，此时return会调用移动构造函数，
	//不会调用复制构造函数
	
	//return s;
	//显示：String(String&&)
	
	return s1;
	//显示：String(const String &)
}
int test2()
{
	getString();
}

#endif

int main(void)
{
	//test0();
	test1();
	//test2();

	return 0;
}
	
