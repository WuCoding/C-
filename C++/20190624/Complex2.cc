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
		cout<<_dreal<<" + "<<_dimag<<"i"<<endl;
	}

	//对象本身发生变化的，就用成员函数形式重载
	//复合赋值运算符 -=  /=  *=  %=
	
	//重载+=复合赋值运算符
	Complex & operator+=(const Complex &rhs)
	//传入运算符右操作数，非静态成员函数默认含有一个this指针，并作为第一个参数
	//运算符的左操作数
	{
		cout<<"Complex & operator+=(const Complex &rhs)"<<endl;
		_dreal+=rhs._dreal;
		_dimag+=rhs._dimag;
		//返回该对象
		return *this;
	}

	//前置++的效率高于后置++的
	
	//前置返回的是引用
	Complex & operator++()
	{
		++_dreal;
		++_dimag;
		return *this;
	}

	//后置返回的是对象
	Complex operator++(int)//int 只是作为一个标识位存在，不需要传递参数
	{
		//先复制构造一个tmp对象
		Complex tmp(*this);
		//对原对象进行自加运算
		++_dreal;
		++_dimag;
		//返回的是tmp对象
		return tmp;
	}

	//友元函数声明
	
	//重载+运算符的函数不能作为类的成员函数，因为成员函数自带this指针作为第一个参数
	friend Complex operator+(const Complex &lhs,const Complex &rhs);
	friend bool operator<(const Complex &lhs,const Complex &rhs);
private:
	//数据成员
	double _dreal;//实部
	double _dimag;//虚部
};

//运算符重载之友元函数
Complex operator+(const Complex &lhs,const Complex &rhs)
{
	return Complex(lhs._dreal+rhs._dreal,lhs._dimag+rhs._dimag);
}

bool operator<(const Complex &lhs,const Complex &rhs)
{
	return lhs._dreal<rhs._dreal;

}

int main(void)
{
	int a=3,b=4;
	int c=a+b;

	&(++a);//++a返回的是a的引用，是左值，可以取地址
	a++;//a++返回的是匿名对象，右值，不能取地址
	
	Complex c1(1,2);
	cout<<"c1=";
	c1.print();
	//显示：
	//c1=1 + 2i

	Complex c2(1,3);
	cout<<"c2=";
	c2.print();
	//显示：
	//c2=1 + 3i

	Complex c3=c1+c2;
	cout<<"c3=";
	c3.print();
	//显示：
	//c3=2 + 5i

	c1+=c2;//改变对象本身的数值的，推荐以成员函数形式重载
	//显示：
	//Complex & operator+=(const Complex &rhs)
	
	cout<<"c1=";
	c1.print();
	//显示：
	//c1=2 + 5i

	cout<<endl<<"c1执行自增运算符："<<endl;
	(++c1).print();
	//显示：
	//3 + 6i
	
	c1.print();
	//显示：
	//3 + 6i

	(c1++).print();
	//显示：
	//3 + 6i
	
	c1.print();
	//显示：
	//4 + 7i

	return 0;
}

