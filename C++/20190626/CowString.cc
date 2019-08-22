#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class CowString
{
	//设计模式之代理模式
	//嵌套类
	class CharProxy
	{
		public:
			//构造函数
			CharProxy(CowString & self,int idx)
			: _self(self)
			, _idx(idx)
			{}

			//重载赋值运算符函数声明
			char & operator=(const char & ch);//考虑到连续赋值于是将返回值设为char
			//重载输出运算符<<函数友元函数声明，输出输入重载函数不能是成员函数
			friend std::ostream & operator<<(std::ostream & os,const CharProxy & rhs);
#if 0
			//类型转换函数，将CharProxy类型转换为char类型
			operator char()
			{
				return _self._pstr[_idx];
			}

#endif
		private:
			//数据成员
			CowString & _self;//存储原本的CowString类的对象的引用
			int _idx;//存储下标
	};

	public:
		//无参构造函数
		CowString()
		: _pstr(new char[1+4]()+4)
		{
			cout<<"CowString()"<<endl;
			initRefcount();//初始化引用计数，将引用计数设为1
		}

		//C风格字符串参数构造函数
		CowString(const char * pstr)
		: _pstr(new char[strlen(pstr)+1+4]()+4)
		{
			cout<<"CowString(const char *)"<<endl;
			initRefcount();//初始化引用计数，将引用计数设为1
			strcpy(_pstr,pstr);
		}

		//复制构造函数
		CowString(const CowString & rhs)
		: _pstr(rhs._pstr)//浅拷贝
		{
			increaseRefcount();//引用计数+1
			cout<<"CowString(const CowString &)"<<endl;
		}

		//赋值运算符重构函数
		CowString & operator=(const CowString & rhs)
		{
			cout<<"CowString & operator=(const CowString &)"<<endl;
			if(this!=&rhs){//防止自复制
				//三部曲
				release();//引用计数-1，同时判断引用计数是否为0，为0则释放堆空间
				//浅拷贝
				_pstr=rhs._pstr;
				//将新的堆空间引用计数+1
				increaseRefcount();
			}
			return *this;
		}

		//析构函数
		~CowString()
		{
			//将引用计数-1，同时判断引用计数是否为0，为0则释放堆空间
			release();
		}

		//获得字符串大小
		int size() const
		{
			return strlen(_pstr);
		}

		//获得字符串
		const char * c_str() const
		{
			return _pstr;
		}

		//获得引用计数
		int refcount() const
		{
			return *(int*)(_pstr-4);
		}

		//重载[]下标运算符，将返回类型设为CharProxy类型对象
		CharProxy operator[](int idx);

		//重载const型[]下标运算符，用于只读形式
		const char & operator[](int idx)const
		{
			return _pstr[idx];
		}

		//输出运算符重载函数友元声明
		friend std::ostream & operator<<(std::ostream & os,const CowString & rhs);
		//该函数使用的是CharProxy类型的私有成员，所以在CharProxy类内设为友元，但是
		//CharProxy类型为CowString类型的私有成员类型，所以也必须将该函数设为CowString
		//类型的友元，才能访问CharProxy类型的私有成员
		friend std::ostream & operator<<(std::ostream & os,const CharProxy & rhs);

	private:
		//初始化引用计数函数
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

		//将引用计数-1，同时判断引用计数是否为0，如果为0，则释放该堆空间
		void release()
		{
			//引用计数-1
			decreaseRefcount();
			if(refcount()==0)
			{
				//引用计数为0，释放该堆内存
				delete [] (_pstr-4);
				cout<<">> delete heap data!"<<endl;
			}
		}
	private:
		//数据成员
		char * _pstr;//指向的是字符串本身
};

//CowString类型的输出运算符重载函数的实现
std::ostream & operator<<(std::ostream & os,const CowString & rhs)
{
	os<<rhs._pstr;
	return os;
}
//CowString类型的下标运算符重载函数的实现，返回的是其内置类型CharProxy类型对象
CowString::CharProxy CowString::operator[](int idx)
{
	return CharProxy(*this,idx);
}

//CharProxy类型的赋值运算符重载函数，执行写操作
char & CowString::CharProxy::operator=(const char & ch)
{
	//_self是CowString类型的对象
	if(_idx>=0&&_idx<_self.size()){//下标未越界
		if(_self.refcount()>1&&_self._pstr[_idx]!=ch){//是共享字符串，且写操作导致字符串改变，此时才进行新空间的开辟
			//先引用计数-1
			_self.decreaseRefcount();
			//开辟新空间，因为需要复制之前字符串的内容，所以不能将新空间的地址直接赋值给
			//_self._pstr，而是先用一个中间量来接
			char *ptmp=new char[_self.size()+1+4]()+4;
			strcpy(ptmp,_self._pstr);
			_self._pstr=ptmp;
			//初始化引用计数
			_self.initRefcount();
		}
		_self._pstr[_idx]=ch;
		return _self._pstr[_idx];
	}else{//访问下标越界
		static char nullchar='\0';
		cout<<"下标越界！"<<endl;
		return nullchar;
	}
}

//CharProxy类型的输出运算符重载函数实现
std::ostream & operator<<(std::ostream & os,const CowString::CharProxy & rhs)
{
	os<<rhs._self._pstr[rhs._idx];
	return os;
}

int main()
{
	CowString s1;
	CowString s2 = s1;
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
	s2[0] = 'h';//CharProxy().operator=(char);
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());

	cout << endl << "执行读操作:" << endl;
	cout << "s3[0] = " << s3[0] << endl;// cout << CharProxy()，这里也可以不用重载输出运算符，可以用类型转换函数，将CharProxy类型隐式转换成char类型 
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());
}













































