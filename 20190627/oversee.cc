#include <iostream>
using std::cout;
using std::endl;

//基类
class Base
{
	public:
		//构造函数
		Base(int x)
		: _x(x)
		{
			cout<<"Base(int)"<<endl;
		}

		//打印函数
		void display() const
		{
			cout<<"Base::_x="<<_x<<endl;
		}
	protected:
		int _x;
};

//派生类
class Derived
: public Base  //以public方式继承
{
	public:
		//传参构造函数
		Derived(int x1,int x2)
		: Base(x1)
		, _x(x2)
		{
			cout<<"Derived(int,int)"<<endl;
		}

		//打印函数 注：这里与基类的打印函数重名
		void display() const
		{
			cout<<"this->_x="<<this->_x<<endl;
			cout<<">>Base::_x="<<Base::_x<<endl;
			//基类的同名_x被隐藏了oversee
			cout<<"_x="<<_x<<endl;
		}

	private:
		//与基类同名的数据成员
		int _x;
};

int main(void)
{
	Derived d1(10,20);
	//基类的display方法也被隐藏了
	d1.display();
	//要想调基类被隐藏的方法解决方案为：使用类名限定
	d1.Base::display();
	//只要派生类中定义的成员函数名与基类相同，基类的同名成员函数被隐藏
	
	return 0;
}

