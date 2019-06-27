#include <iostream>
#include <limits>
using std::cout;
using std::endl;

class Point
{
	public:
		//构造函数
		Point(int ix=0,int iy=0)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"("<<_ix<<","<<_iy<<")";
		}
		//声明友元类和友元函数，友元声明在public、private、protect都可以
		friend class Complex;//如果Complex类在之前定义则可以省略class，在之后定义则要加上class
		//声明输出运算符重载函数为友元函数
		friend std::ostream & operator<<(std::ostream &os,const Point & rhs);
	private:
		int _ix;
		int _iy;
};
//输出运算符重载函数的实现
std::ostream & operator<<(std::ostream &os,const Point & rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

class Complex
{
	public:
		//构造函数
		Complex(double dreal,double dimag)
		: _dreal(dreal)
		, _dimag(dimag)
		{}

		//将Point类的对象来初始化Complex类的对象
		//explicit
		Complex(const Point & rhs)
		: _dreal(rhs._ix)
		, _dimag(rhs._iy)
		{
			cout<<"Complex(const Point & )"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<_dreal<<"+"<<_dimag<<"i"<<endl;
		}

		//复合赋值运算符+=重载函数，复合赋值运算符（-=  /=  *=  %=）
		Complex & operator+=(const Complex & rhs)
		{
			cout<<"Complex & operator+=(const Complex & rhs)"<<endl;
			_dreal+=rhs._dreal;
			_dimag+=rhs._dimag;
			return *this;
		}//对象本身发生变化的，就用成员函数形式重载

		//前置++运算符重载函数，前置返回的是引用，所以效率高于后置
		Complex & operator++()
		{
			++_dreal;
			++_dimag;
			return *this;
		}

		//后置++运算符重载函数，后置返回的是对象
		Complex operator++(int)//int 只是作为一个标识位存在，并无实际意义，不需要传递参数
		{
			//用一个局部对象来存自加之前对象的值
			Complex tmp(*this);
			++_dreal;
			++_dimag;
			return tmp;
		}
		//输入输出流运算符都不能以成员函数形式重载
		//因为输入输出流运算符都要求左操作数为流对象
		//如果以成员函数形式进行重载，则左操作数是对象本身
		//
		//std::ostream & operator<<(std::ostream & os)
		//该函数的实际样式为：
		//std::ostream & operator<<(Complex *this,std::ostream & os)
		//这个函数第一个参数为左操作数，第二个参数为右操作数。
		//this>>os;这明显不对，所以输入输出流运算符不能以成员函数
		//形式重载

		//友元声明
		//+运算符重载函数
		friend Complex operator+(const Complex & lhs,const Complex & rhs);
		//<运算符重载函数
		friend bool operator<(const Complex & lhs,const Complex & rhs);
		//<<输出流运算符重载函数
		friend std::ostream & operator<<(std::ostream & os,const Complex & rhs);
		//>>输入流运算符重载函数
		friend std::istream & operator>>(std::istream & is,Complex & rhs);
	private:
		double _dreal;
		double _dimag;
};

//运算符重载之友元函数的实现
Complex operator+(const Complex & lhs,const Complex & rhs)
{
	return Complex(lhs._dreal+rhs._dreal,lhs._dimag+rhs._dimag);
}

bool operator<(const Complex & lhs,const Complex & rhs)
{
	return lhs._dreal<rhs._dreal;
}

std::ostream & operator<<(std::ostream & os,const Complex & rhs)
{
	os<<rhs._dreal<<"+"<<rhs._dimag<<"i";
	return os;
}

//该函数为了构造一个健壮的读入流的操作，防止因流输入的数据与变量类型不匹配造成流的异常
void readDoubleValue(std::istream & is,double & value)
{
	cout<<"pls input a valid double:"<<endl;
	while(is>>value,!is.eof())//将流中数据输入到变量中，如果流未到达文件尾，继续执行输入
	{
		if(is.bad())//如果流崩溃，直接退出
		{
			cout<<"istream is corrupted!"<<endl;
			return;
		}else if(is.fail()){//如果流中数据类型错误造成流的状态异常
			is.clear();
			is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//第二个参数表示遇到换行符结束
			cout<<"pls input a valid double:"<<endl;
			continue;
		}
		break;
	}
}

std::istream & operator>>(std::istream & is,Complex & rhs)
{
	readDoubleValue(is,rhs._dreal);
	readDoubleValue(is,rhs._dimag);

	return is;
}
int test0(void)
{
	//对一些类的重载运算符进行测试，并与内置运算符进行比较
	int a=3,b=4;
	int c=a+b;
	//a+=b;
	//a=a+b;
	
	&(++a);//因为++a是左值可以取地址
	(a++);//a++是右值，一个临时对象，不能进行取地址操作

	//用类对象来执行像内置类型执行内置运算符的操作
	Complex c1(1,2);
	cout<<"c1=";
	c1.print();

	Complex c2(1,3);
	cout<<"c2=";
	c2.print();

	Complex c3=c1+c2;
	cout<<"c3=";
	c3.print();

	//对象本身发生变化的，用成员函数形式重载
	c1+=c2;
	cout<<"c1=";
	c1.print();

	cout<<endl<<"c1执行自增运算符："<<endl;
	(++c1).print();
	c1.print();
	
	(c1++).print();//临时对象调用print()函数
	c1.print();

	return 0;
}

int test1()
{
	//对重载的输入输出运算符进行测试
	int a=3;
	cout<<"a="<<a<<endl;

	Complex c1(1,2);
	cout<<"c1="<<c1<<endl;

	std::cin>>c1;
	cout<<"c1="<<c1<<endl;

	return 0;
}

int test2()
{
	//对Complex的Complex(const Point & rhs)构造函数进行测试
	Point pt(11,12);
	cout<<"pt="<<pt<<endl;

	Complex c1=pt;//通过构造函数进行，隐式转换
	cout<<"c1="<<c1<<endl;

	return 0;
}

int main(void)
{
	test0();
	test1();
	test2();

	return 0;
}




























