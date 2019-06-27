#include<iostream>
using std::cout;
using std::endl;
//只能生成栈空间对象
//将new运算符和delete运算符隐藏起来

class StackPoint
{
	public:
		StackPoint(int ix,int iy)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"StackPoint(int,int)"<<endl;
		}

		void print() const
		{
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}

		~StackPoint()
		{
			cout<<"~StackPoint()"<<endl;
		}
	private:
		static void* operator new(size_t sz);
		static void operator delete(void* pointer);
	private:
		int _ix;
		int _iy;
};

int main(void)
{
	//创建栈空间的对象
	StackPoint sp1(5,6);
	sp1.print();
	//创建一个堆空间的对象
	//StackPoint* psp=new StackPoint(7,8);
	//psp->print();
	

	return 0;
}
