#include <iostream>
using std::cout;
using std::endl;

//基类
class Point
{
	public:
		//构造函数
		Point(int ix=0,int iy=0)
		: _ix(ix) //private型数据成员
		, _iy(iy) //protected型数据成员
		{
			cout<<"Point(int,int)"<<endl;
		}

		//打印函数
		void display() const
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}

	protected:
		//对派生类内部开放
		
		//获得private型数据成员
		int getX() const
		{
			return _ix;
		}

		//protected型数据成员
		int _iy;

	private:
		//private型数据成员
		int _ix;
};

//Point类的派生类
class Point3D
: private Point                //以private方式继承，使得所有Point基类的非私有成员在派生类Point3D类中
{	                       //都以private型成员存在，使得以Point3D为基类的派生类无法访问到Point类
	public:	               //的成员，相当于一条派生类的链在此类处断裂
		//构造函数
		Point3D(int ix=0,int iy=0,int iz=0)
		: Point(ix,iy) //主动调用基类的构造函数
		, _iz(iz)      //本类的数据成员初始化
		{
			cout<<"Point(int,int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			//cout<<_ix;
			//该语句错误原因：
			//       >派生类内部不能访问基类的私有成员
			cout<<"("<<getX()<<","<<_iy<<","<<_iz<<")"<<endl;
			//getX()、_iy都为基类Point的protected型成员，在被Point3D类以private方式
			//继承之后，在Point3D中以private型成员存在，对外部与以Point3D为基类的派
			//生类的内部都不可访问
		}

	private:
		//数据成员
		int _iz;
};
//以Point3D为基类的派生类
class Point4D
: protected Point3D      //以protected形式继承，在类的内部只能访问Point3D的非私有成员，而且Point类被
{	                 //Point3D类以private方式继承，所以Point4D内部无法访问Point类的非私有成员
	public:
#if 0
		//调用Point类的protected型成员getX()
		void show() const
		{
			cout<<getX();
		}
#endif

	private:
		//数据成员
		int _im;
};

int main(void)
{
	//Point4D pt;
	//pt.show();
	//该语句执行失败原因：
	//     >getX()为Point类的protected型成员，被Point3D以private方式继承之后，以private型
	//     >成员存在于Point3D类中，属于Point3D类的私有成员，以Point3D为基类的派生类内部，是
	//     >无法访问到基类的私有成员的
	return 0;
}





































