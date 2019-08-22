#include <string.h>

#include <iostream>
using std::cout;
using std::endl;
//自己写出写时复制的string类
class CowString
{
	//该类在堆内存中是前4个字节存储int类型的引用计数，之后才是存储字符串
	public:
		
		//无参构造函数
		CowString()
		: _pstr(new char[1+4]()+4)//_pstr指向的是字符串首地址，而不是引用计数
		{
			cout<<"CowString()"<<endl;
			initRefcount();//初始化引用计数
		}
		
		//c风格字符串传参构造函数
		CowString(const char *pstr)
		: _pstr(new char[strlen(pstr)+1+4]()+4)
		{
			cout<<"CowString(const char*)"<<endl;
			initRefcount();//初始化引用计数
			strcpy(_pstr,pstr);
		}

		//复制构造函数，指向同一个堆内存地址，执行的是浅拷贝，将引用计数+1
		CowString(const CowString & rhs)
		: _pstr(rhs._pstr)//浅拷贝
		{
			increaseRefcount();//引用计数+1
			cout<<"CowString(const CowString &)"<<endl;
		}

		//赋值运算符重载函数，也是进行三部曲
		CowString & operator=(const CowString & rhs)
		{
			cout<<"CowString & operator=(const CowString &)"<<endl;
			if(this!=&rhs){//防止自复制
				release();//将之前的地址的引用计数-1，同时判断引用计数是否为0，为0则释放该堆空间
				_pstr=rhs._pstr;//浅拷贝
				increaseRefcount();//将引用计数+1
			}
			return *this;
		}

		//析构函数
		~CowString()
		{
			release();//将指向的空间的引用计数-1，同时判断引用计数是否为0，为0则释放该堆空间
		}

		//获得字符串的大小
		int size() const
		{
			return strlen(_pstr);
		}

		//获得该字符串
		const char * c_str() const
		{
			return _pstr;
		}

		//获得该字符串的引用计数
		int refcount() const
		{
			return *(int*)(_pstr-4);
		}

		//重载下标运算符[]函数的声明
		char & operator[](int idx);

		//重载const型下标运算符[]函数，该函数只提供读操作，不提供写操作
		const char & operator[](int idx) const
		{
			return _pstr[idx];
		}

		//友元函数声明
		//输出流运算符重载函数
		friend std::ostream & operator<<(std::ostream & os,const CowString & rhs);
	private:
		//初始化引用计数
		void initRefcount()
		{
			*(int*)(_pstr-4)=1;
		}

		//引用计数+1
		void increaseRefcount()
		{
			++*(int*)(_pstr-4);
		}

		//引用计数-1
		void decreaseRefcount()
		{
			--*(int*)(_pstr-4);
		}

		//解除引用，引用计数-1，同时判断引用计数是否为0，为0则释放该堆空间
		void release()
		{
			decreaseRefcount();//执行引用计数-1
			if(refcount()==0){//引用计数为0，释放堆内存
				delete [] (_pstr-4);
				cout<<">> delete heap data!"<<endl;
			}
		}
	private:
		char *_pstr;//指向的是字符串本身
};
//重载输出运算符函数实现
std::ostream & operator<<(std::ostream & os,const CowString & rhs)
{
	os<<rhs._pstr;
	return os;
}
//下标访问运算符的实现不能区分接下来的操作是读操作还是写操作
char & CowString::operator[](int idx)
{
	if(idx>=0&&idx<size()){
		if(refcount()>1){//该字符串被多个共享，执行深拷贝
			decreaseRefcount();//使之前的引用计数-1

			//重新开辟一个新的堆空间，因为还要进行复制，所以先用一个中间指针来接收空间首地址
			char *ptmp=new char[size()+1+4]()+4;
			strcpy(ptmp,_pstr);
			_pstr=ptmp;
			initRefcount();
		}
		return _pstr[idx];
	}else{
		static char nullchar='\0';
		cout<<"下标越界！"<<endl;
		return nullchar;
	}
}

int main(void)
{
	CowString s1;
	CowString s2 = s1;//复制构造
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;

	CowString s3 = "hello,world";
	CowString s4 = s3;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());

	cout << "执行s2 = s4 之后:" << endl;
	s2 = s4;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());

	cout << endl << "执行写操作：" << endl;
	s2[0] = 'H';
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());

	cout << endl << "执行读操作:" << endl;
	cout << "s3[0] = " << s3[0] << endl; 
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());

}

