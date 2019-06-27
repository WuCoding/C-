#include <string.h>

#include <iostream>
using std::cout;
using std::endl;
//静态数据对象和静态成员函数
class Computer
{
	public:
	//构造函数
		Computer(const char *brand,double price)
		: _brand(new char[strlen(brand)+1]())//深拷贝
		, _price(price)
		{
			strcpy(_brand,brand);
			cout<<"Computer(const char*,double)"<<endl;
			//_totalPrice静态数据对象
			_totalPrice+=_price;
		}
	//复制构造函数
		Computer(const Computer &rhs)
		: _brand(new char[strlen(rhs._brand)+1]())
		, _price(rhs._price)
		{
			strcpy(_brand,rhs._brand);
			cout<<"Computer(const Computer&)"<<endl;
		}
	//赋值运算符
		Computer& operator=(const Computer &rhs)
		{
			//三部曲
			cout<<"Computer & operator=(const Computer &)"<<endl;
			if(this!=&rhs){//防止自复制
				delete [] _brand;//回收左操作数开辟的空间
				_brand=new char[strlen(rhs._brand)+1]();//为左操作数在开辟一个新的堆空间
				strcpy(_brand,rhs._brand);//进行复制

				this->_price=rhs._price;
			}
			return *this;
		}
	//打印函数
		void print()
		{
			cout<<"    brand:"<<this->_brand<<endl
				<<"    price:"<<this->_price<<endl;
		}
	//静态成员函数
		static void printTotalPrice()
		{
			//静态成员函数没有隐含的this指针，所以他无法访问单个对象的数据成员，所以
			//静态成员函数中不能有非静态成员
			//但静态数据成员位于全局/静态区，可以被所有的对象访问，所以静态成员函数
			//中可以有静态数据成员
			//静态成员函数也是所有类对象共享的
			cout<<"    total price:"<<_totalPrice<<endl;
		}

	//析构函数
		~Computer()
		{
			delete [] _brand;
			cout<<"~Computer()"<<endl;
		}
	private:
		char *_brand;
		double _price;
		//静态成员位于全局静态区，被整个类所创建的所有对象共享
		static double _totalPrice;
};

//在全局的位置对静态数据成员进行初始化
double Computer::_totalPrice=0;

void test0()
{
	//打印结果为16 即char* 8个字节 double 8个字节，而静态数据成员位于全局静态区不被算入大小
	cout<<"sizeof(Computer)="<<sizeof(Computer)<<endl;
	Computer pc1("MateBook",6666);
	cout<<">>pc1:"<<endl;
	pc1.print();
	//不仅单个对象可以访问静态成员函数，	
	pc1.printTotalPrice();
	//用类的限定符也可以访问静态成员函数
	Computer::printTotalPrice();

	Computer pc3("Thinkpad",8888);
	cout<<">>pc3:"<<endl;
	pc3.print();
	//静态成员函数可以直接通过类名调用
	Computer::printTotalPrice();
}

int main(void)
{
	test0();
	Computer::printTotalPrice();
	return 0;
}





