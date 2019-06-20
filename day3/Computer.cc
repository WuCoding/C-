#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

class Computer
{
	public:
		//构造函数
		Computer(const char *brand,double price)//使用const char*类型来接是因为：传入的实参为常量字符串时，用char*来接会发生类型不匹配，而用const char*来接既可以接char*类型，也可以来接const char*
		: _brand(new char[strlen(brand)+1]())//深拷贝，重新开辟一块堆内存，来赋值，而不是_brand(brand)这样只是将brand字符串的地址赋给了_brand,brand和_brand都指向同一地址
		, _price(price)
		{
			strcpy(_brand,brand);
			cout<<"Computer(const char*,double)"<<endl;
		}

		//复制构造函数
		Computer(const Computer &rhs)
		: _brand(new char[strlen(rhs._brand)+1]())
		, _price(rhs._price)
		{
			strcpy(_brand,rhs._brand);
			cout<<"Computer(const Computer&)"<<endl;
		}
		
		//赋值运算符函数
		Computer & operator=(const Computer &rhs)
		{
			//三部曲
			cout<<"Computer & operator=(const Computer &)"<<endl;
			if(this!=&rhs){//防止自复制 即a=a
				//第一部曲，回收左操作数开辟的空间
				delete [] _brand;
				//第二部曲，重新为左操作数开辟空间
				_brand=new char[strlen(rhs._brand)+1]();
				//第三部曲，进行复制
				strcpy(_brand,rhs._brand);

				this->_price=rhs._price;
			}
			return *this;
		}
		
		void print()
		{
			printf("    brand=%p\n",_brand);//%p是打印地址
			cout<<"    brand:"<<_brand<<endl
				<<"    price:"<<_price<<endl;
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
};

void test0()
{
	Computer pc1("MateBook",6666);
	cout<<">>pc1:"<<endl;
	pc1.print();

	//用一个已经存在的对象初始化另一个新对象
	Computer pc2=pc1;
	cout<<">>pc2:"<<endl;
	pc2.print();

	Computer pc3("Thinkpad",8888);
	cout<<">>pc3:"<<endl;
	pc3.print();

	//对类的对象进行赋值操作
	pc3=pc1;//     pc3.operator=(pc1) Computer::operator=(&pc3,pc1)
	cout<<">>pc3:"<<endl;
	pc3.print();

	//自复制
	pc2=pc2;
}

int main(void)
{
	test0();
	return 0;
}


































