#include <iostream>
using std::cout;
using std::endl;

//创建一个只能在堆空间上创建对象的类
//方法：将析构函数隐藏

class HeapPoint
{
	public:
		HeapPoint(int ix,int iy)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"HeapPoint(int,int)"<<endl;
		}
		
		void print() const
		{
			cout<<"("<<this->_ix<<","<<this->_iy<<")"<<endl;
		}

		void destroy()
		{
			delete this;
		}
	private:
		~HeapPoint()
		{
			cout<<"~HeapPoint()"<<endl;
		}
	private:
		int _ix;
		int _iy;
};

int main(void)
{
	//创建栈空间对象
	//HeapPoint hp(3,4);
	//hp.print();
	//创建堆空间对象
	HeapPoint* php=new HeapPoint(5,6);
	//delete php;
	php->destroy();
	return 0;
}

