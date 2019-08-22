#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Base
{
	public:
		//构造函数
		Base(const char * base)
		: _base(new char[strlen(base)+1]())
		{
			cout<<"Base(double)"<<endl;
			strcpy(_base,base);
		}
		//打印函数 虚函数
		virtual
		void print() const
		{
			cout<<"Base::_base="<<_base<<endl;
		}
		
		//规定：一旦当类中定义了虚函数，都要将析构函数设为虚函数，
		//因为当类中定义了虚函数，就会产生一种用基类指针指向派生类
		//对象的用法，对象为堆对象时，delete一个指向派生类的基类指针
		//只会执行基类的析构函数，而不会执行派生类的析构函数，所以将
		//析构函数设为虚函数，将会根据指针所指对象的类型来调用析构函数
		//虽然每个类的析构函数名字不同，但因为每个类只有一个析构函数，
		//所以也和其他虚函数一样

		//析构函数 虚函数
		virtual
		~Base()
		{
			delete []_base;
			cout<<"~Base()"<<endl;
		}
	private:
		//数据成员
		char * _base;
};

//派生类
class Derived
: public Base //以public的方式继承
{
	public:
		//构造函数
		Derived(const char *base,const char *derived)
		: Base(base)
		, _derived(new char[strlen(derived)+1]())
		{
			cout<<"Derived(double,double)"<<endl;
			strcpy(_derived,derived);
		}

		//打印函数 虚函数
		void print() const
		{
			Base::print();  //调用基类的打印函数（虚函数），因为被类名限制
			cout<<"Derived::_derived="<<_derived<<endl;
		}

		//析构函数，因为基类已经将析构函数设为虚函数，所以该析构函数也为虚函数
		~Derived()
		{
			delete []_derived;
			cout<<"~Derived()"<<endl;
		}

	private:
		//数据成员
		char *_derived;
};

int main(void)
{
	//基类的指针指向一个派生类的堆对象
	Base *pbase=new Derived("hello","world");
	pbase->print();  //调用的是派生类的print()函数
	delete pbase; //使用虚函数机制，此时调用的是派生类的析构函数，如果没有将基类的
	              //析构函数设为虚函数，那么此时调用的则是基类的析构函数，但是该指针
		      //指向的是一个派生类的对象，这样就会导致销毁对象失败
#if 0
	Derived *pderived=(Derived*)pbase;
	delete pderived;  //这里调用的是派生类的析构函数
#endif
	return 0;
}












































