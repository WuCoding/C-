#include <iostream>
using std::cout;
using std::endl;

//这个程序用来证明虚函数表是存在的
class Base
{
	public:
		//构造函数
		Base(long data)
		: _data(data)
		{}

		virtual 
		void func1() const
		{
			cout<<"Base::func1()"<<endl;
		}

		virtual
		void func2() const
		{
			cout<<"Base::func2()"<<endl;
		}

		virtual
		void func3() const
		{
			cout<<"Base::func3()"<<endl;
		}

	private:
		//数据成员
		long _data;    //8字节
};

int main(void)
{
	Base base(10);

	long **pvtable=(long**)&base;//pvtable为指向long型数据的指针数组

	long address=pvtable[0][0];
	//因为指针也是8个字节，在base对象中前8字节存储vfptr，而vfptr指向一个地址，该地址又
	//存放有多个指针（函数入口），可以用指向long型数据的指针数组来获取
	
	typedef void(*Function)();  //定义Function类型为一个无返回值的无参函数指针
	Function f=(Function)address; //将该地址类型转换为一个函数指针，这个就是虚表中的
	                               //第1个函数入口地址。
	f();//调用该函数指针

	f=(Function)pvtable[0][1];//指向虚表中的第2个函数
	f();//调用该函数指针

	f=(Function)pvtable[0][2];//指向虚表中的第3个函数
	f();//调用该函数指针

	cout<<long(pvtable[1])<<endl; //在Base类的对象中，第2个8字节存储的是该类的数据成员
	                              //long型数据_data
	return 0;
}
