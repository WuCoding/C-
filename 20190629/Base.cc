#include <iostream>
using std::cout;
using std::endl;

//一个类不能被继承，在定义类的时候，在类名后加上final关键字
class Base final
{
	public:
		//构造函数
		Base()
		{}
	private:
		//数据成员
		int _base;
};

class Derived
: public Base  //以public方式继承，但由于Base类后加了final关键字，所以在编译时，将会报错
{
	public:
		//构造函数
		Derived()
		: Base()
		{}
};

int main(void)
{
	Derived derived;
}
