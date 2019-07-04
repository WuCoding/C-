#include <iostream>
using std::cout;
using std::endl;

//-----------------------------函数模板作为成员函数----------------------------------

//非模板的类
class Example
{
	public:
		//构造函数
		Example(double data)
		: _data(data)
		{}

		//函数模板还可以是一个成员函数形式
		//类型转换函数
		template <class T>
		T typecast()
		{
			return T(_data);
		}
	private:
		//数据成员
		double _data;
};

int main(void)
{
	Example e(11.11);
	cout<<e.typecast<int>()<<endl;
	//显示：11

	return 0;
}
