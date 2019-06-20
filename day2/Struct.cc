#include <iostream>
using std::cout;
using std::endl;

//struct的默认访问权限是public
struct Example
{
	public:
		//构造函数
		Example(int x)
		:_iy(x)
		,_ix(_iy)
		{

		}
		void setX(int ix)
		{
			_ix=ix;
		}
		void setY(int iy)
		{
			_iy=iy;
		}
		void print()
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}
	private:
		int _ix;
		int _iy;
};
//此函数测试的是对对象的数据成员的初始化
//构造函数对数据成员的初始化顺序是按数据成员定义的顺序，而不是初始化的顺序
int main(void)
{
	Example el(1);

	el.print();

	return 0;
}

