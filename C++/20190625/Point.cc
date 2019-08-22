#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

class Complex
{
	public:
		//构造函数
		Complex(double dreal,double dimag)
		: _dreal(dreal)
		, _dimag(dimag)
		{}

		//打印函数
		void print() const
		{
			cout<<_dreal<<"+"<<_dimag<<"i"<<endl;
		}

		//重构+=运算符（复合赋值运算符  -=  /=  *=  %= ）
		Complex & operator+=(const Complex & rhs)
		{
			cout<<"Complex & operator+=(const Complex & rhs)"<<endl;
			_dreal+=rhs._dreal;
			_dimag+=rhs._dimag;
			return *this;
		}//对象本身发生变化的，就用成员函数形式重载

		//重载前置++运算符，因为前置++返回的是引用，所以前置++的效率高于后置++
		Complex & operator++()
		{
			++_dreal;
			++_dimag;
			return *this;
		}

		//重载后置++运算符，后置++返回的是对象
		Complex operator++(int)//int只是作为区分后置++和前置++的标志，并无实际意义，只是作为一个标识位存在，不需要传递参数
		{
			//先用一个临时对象存储当前对象的数值
			Complex tmp(*this);
			++_dreal;
			++_dimag;
			return tmp;
		}

		//输出运算符<<重载函数作为友元函数
		friend std::ostream & operator<<(std::ostream & os,const Complex & rhs);
	private:
		double _dreal;
		double _dimag;
};
//输出运算符<<重载函数的实现
std::ostream & operator<<(std::ostream & os,const Complex & rhs)
{
	os<<rhs._dreal<<"+"<<rhs._dimag<<"i";
	return os;
}

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

		//类型转换函数特点：将该类型转换为其他类型
		//1. 成员函数
		//2. 没有返回值类型
		//3. 没有形参
		//4. 在函数体内必须以return语句返回一个目标类型的变量
		//
		//尽量不要使用

		//将Point类型转换为int类型
		operator int()
		{
			cout<<"operator int()"<<endl;
			return _ix;
		}
#if 1	
		//将Point类型转换为double类型
		operator double()
		{
			cout<<"operator double()"<<endl;
			return _ix*_iy;
		}
#endif
		//将Point类型转换为Complex类型
		operator Complex()
		{
			return Complex(_ix,_iy);
		}

		//输出运算符<<重载函数作为友元函数
		friend std::ostream & operator<<(std::ostream &os,const Point &rhs);
	private:
		int _ix;
		int _iy;
};

//输出运算符<<重构函数的实现
std::ostream & operator<<(std::ostream &os,const Point & rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

int main(void)
{
	Point pt1(1,2);
	cout<<"pt1="<<pt1<<endl;

	pt1=10;//隐式类型转换，调用了构造函数，步骤为：1.先用10调用构造函数产生一个临时对象，再将临时对象赋值给pt1
	cout<<"pt1="<<pt1<<endl;

	int x=pt1;//要调用int类型转换函数
	cout<<"x="<<x<<endl;

	double y=pt1;//调用double类型转换函数，如果未创建double类型转换函数，则会调用int类型转换函数，然后再转换为double类型
	cout<<"y="<<y<<endl;
	//违反常规思维，一般情况下不建议使用
	Complex c=pt1;//调用Complex类型转换函数
	cout<<"c="<<c<<endl;
	return 0;
}





























