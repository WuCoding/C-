#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class Computer
{
	public:
		Computer(const char *brand,double price)
		//: _brand(brand)//浅拷贝，只传地址
		: _brand(new char[strlen(brand)+1]())//深拷贝
		, _price(price)
		{
			strcpy(_brand,brand);
			cout<<"Computer(const char*,double)"<<endl;
		}

		void print()
		{
			cout<<"  brand:"<<_brand<<endl
				<<"  price:"<<_price<<endl;
		}
		//对象销毁的过程中会自动调用析构函数
		//
	
		
		
	//问题：执行了析构函数就是销毁了对象？
	#if 0
		void release()
		{
			delete [] _brand;
		}
	#endif
		
	//析构函数，作用：用来回收对象申请的资源
		~Computer()
		{
			if(_brand){//_brand没有被销毁，则进行销毁
				delete [] _brand;
				_brand=nullptr;//NULL
			}
			cout<<"~Computer()"<<endl;
		}
	private:
		char *_brand;
		double _price;
};
//全局变量对象
Computer pc2("Xiaomi",7500);

int test0(void)
{
	{
		//局部变量对象
		Computer pc1("MateBook",6666);
		cout<<">>pc1:"<<endl;
		pc1.print();
	}

	cout<<">>pc2:"<<endl;
	pc2.print();

	//堆空间的对象的销毁，需要手动执行
	Computer *pc3=new Computer("Thinkpad",7777);
	cout<<">>pc3:"<<endl;
	pc3->print();
	//执行delete表达式的过程中，就会调用析构函数
	delete pc3;

	//静态变量对象
	static Computer pc4("Macbook pro",20000);
	cout<<">>pc4:"<<endl;
	pc4.print();
	
	return 0;
}

void test1()
{
	//堆空间上的类的对象
	Computer *pc3=new Computer("Thinkpad",7777);
	cout<<">>pc3:"<<endl;
	pc3->print();
	//该语句被执行之后，对象是没有被销毁的
	pc3->~Computer();
	delete pc3;

}

void test2()
{
	Computer pc1("MateBook",6666);
	cout<<">>pc1:"<<endl;
	pc1.print();
	//析构函数可以主动调用，但不这样做，析构函数应该让其自动执行
	pc1.~Computer();
}

int main(void)
{
	test1();
	test2();
	return 0;
}



















