#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

//自定义类类型，都要大写首字母
class Computer
{
	//public成员可以在类之外访问，public成员称为类对外的接口、功能、服务
	public:
		//对成员函数采用驼峰方式进行命名
		void setBrand(const char *brand)
		{
			strcpy(_brand,brand);
		}

		void setPrice(double price)
		{
			_price=price;
		}
	//protected://保护成员不能在类之外访问
		void print()
		{
			cout<<"brand:"<<_brand<<endl
				<<"price:"<<_price<<endl;
		}
	//私有成员尽量放到类的底部，私有的成员不能在类之外访问
	private:
		char _brand[20];
		double _price;
};//注意类的大括号后要加 ';'
int main(void)
{
	Computer pc1;
	pc1.setBrand("Thinkpad");
	pc1.setPrice(8888);
	pc1.print();

	return 0;
}
