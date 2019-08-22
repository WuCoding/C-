#include <iostream>
using std::cout;
using std::endl;

class Complex
{
public:
	//构造函数
	Complex(double dreal,double dimag)
	: _dreal(dreal)//复数实部
	, _dimag(dimag)//复数虚部
	{}

	//打印函数
	void print() const
	{
		cout<<_dreal<<" + "<<_dimag<<"i"<<endl;
	}

	//获得实部
	double getReal() const
	{
		return _dreal;
	}
	//获得虚部
	double getImage() const
	{
		return _dimag;
	}

private:
	//数据成员
	double _dreal;
	double _dimag;//i^2=-1 欧拉公式
};

//运算符重载之普通函数
Complex operator+(const Complex &lhs,const Complex &rhs)
{
	return Complex(lhs.getReal()+rhs.getReal(),lhs.getImage()+rhs.getImage());
}

int main(void)
{
	int a=3,b=4;
	int c=a+b;

	Complex c1(1,2);
	cout<<"c1=";
	c1.print();
	//显示：
	//c1=1+2i

	Complex c2(1,3);
	cout<<"c2=";
	c2.print();
	//显示：
	//c2=1+3i

	Complex c3=c1+c2;
	cout<<"c3=";
	c3.print();
	//显示：
	//c3=2+5i

	return 0;
}
