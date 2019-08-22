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

	void print() const
	{
		cout<<_dreal<<" + "<<_dimag<<"i"<<endl;
	}

	//运算符重载之成员函数
	Complex operator+(const Complex &rhs)
	{
		return Complex(_dreal+rhs._dreal,_dimag+rhs._dimag);
	}

private:
	//数据成员
	double _dreal;//实部
	double _dimag;//虚部
};

#if 1
int operator+(int x,int y)
{
	return x-y;
}
#endif

int main(void)
{
	int a=3,b=4;
	int c=a+b;


	Complex c1(1,2);
	cout<<"c1=";
	c1.print();

	Complex c2(1,3);
	cout<<"c2=";
	c2.print();

	Complex c3=c1+c2;
	cout<<"c3=";
	c3.print();

	return 0;
}
