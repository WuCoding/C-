#include <iostream>
using std::cout;
using std::endl;

#pragma pack(push)//预处理指令 指定内存对齐字节数
#pragma pack(4)   //内存对齐字节数为4

class Base
{
	public:
		//构造函数
		Base(int & ref)
		: _ref(ref)
		{}

		//打印函数 虚函数
		virtual
		void display() const
		{
			cout<<"display()"<<endl;
		}

	private:
		//数据成员
		int _a;//--------------------------------------4
		double _b;//-----------------------------------8
		short _c[5];//---------------------------------10
		char _d;//-------------------------------------1
		static int _e;//-------------------------------4
		int & _ref;//----------------------------------8
};

#pragma pack(pop)

class Base2
{
	public:
		//构造函数
		Base2(int & ref)
		: _ref(ref)
		{}

		//打印函数 虚函数
		virtual
		void display() const
		{
			cout<<"display()"<<endl;
		}

	private:
		//数据成员
		int _a;//-------------------------------------4
		double _b;//----------------------------------8
		short _c[5];//--------------------------------10
		char _d;//------------------------------------1
		static int _e;//------------------------------4
		int & _ref;//---------------------------------8
};

int main(void)
{
	//系统是32位的还是64位
	
	//Base类是以4字节对齐------结果为40
	cout<<"sizeof(Base)="<<sizeof(Base)<<endl;
	//Base2类是以8字节对齐-------结果为48
	cout<<"sizeof(Base2)="<<sizeof(Base2)<<endl;

	return 0;
}








































