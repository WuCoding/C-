#include <iostream>
using std::cout;
using std::endl;

//类模板
template<class Type>
class RAII
{
	public:
		//构造函数
		explicit
		RAII(Type *pointer)
		: _pointer(pointer)
		{}

		//->运算符重构函数
		Type * operator->()
		{
			return _pointer;
		}
		
		//*运算符重构函数
		Type & operator*()
		{
			return *_pointer;
		}

		//获得_pointer数据成员函数
		Type * get()
		{
			return _pointer;
		}

		//重置指针的值
		void reset(Type * pointer)
		{
			if(_pointer){
				//释放原有空间
				delete _pointer;
			}
			_pointer=pointer;
		}

		//析构函数
		~RAII()
		{
			if(_pointer){
				delete _pointer;
			}
		}
	private:
		//数据成员
		Type *_pointer;
};

class Point
{
	public:
		//构造函数
		Point(int ix=0,int iy=0)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}

		//析构函数
		~Point()
		{
			cout<<"~Point()"<<endl;
		}

		//友元函数声明
		friend std::ostream & operator<<(std::ostream &os,const Point &rhs);
	private:
		//数据成员
		int _ix;
		int _iy;
};

//输出运算符重载函数实现
std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix<<","<<rhs._iy<<")";
	return os;
}

int main(void)
{
	//智能指针的雏形
	RAII<Point> pointer(new Point(1,2));
	//显示：Point(int,int)
	pointer->print();
	//显示：（1，2）
	(*pointer).print();
	//显示：（1，2）

	cout<<"*pointer="<<*pointer<<endl;
	//显示：*pointer=(1,2)

	return 0;
	//显示：~Point()
}














































