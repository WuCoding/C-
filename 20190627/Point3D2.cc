#include <iostream>
using std::cout;
using std::endl;
//基类
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
		void display() const
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}

	protected:
		//protected成员对派生类内部开放
		
		//获取数据成员函数
		int getX() const
		{
			return _ix;
		}

		//protected数据成员
		int _iy;

	private:
		//private私有成员，对于派生类是不可见的
		int _ix;
};
//派生类无法继承基类构造和析构函数
//Point的派生类
class Point3D
:protected Point //以protected方式继承，基类private成员在派生类内部无法访问，
{	         //基类public、protected成员在派生类中以protect成员形式存在
	public:
		//构造函数
		Point3D(int ix,int iy,int iz)
		: Point(ix,iy)  //主动调用Point类的构造对象
		, _iz(iz)       //派生类自己的数据成员初始化
		{
			cout<<"Point(int,int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			//cout<<_ix;  因为基类private成员对派生类内部不可见，所以这句语句无法执行
			cout<<"("<<getX()<<","<<_iy<<","<<_iz")"<<endl;
			//getX()、_iy是基类的protected成员，是基类的非私有成员，可以被派生类内部访问
			//采用protected继承之后，基类的非私有成员在派生类内部都变成protected型
		}

	private:
		//数据成员
		int _iz;
};

//Point3D的派生类
class Point4D
: protected Point3D
{
	public:
		//调用Point类protected成员getX()，被Point3D类以protected方式继承，
		//所以以protected型成员存在于Point3D类中，为非私有成员，可以被Point3D
		//的派生类内部访问
		void show () const
		{
			cout<<getX();
		}

	private:
		//数据成员
		int _im;
};

int main(void)
{
	Point3D pt1(1,2,3);
	
	//pt1.display(); 
	//该语句执行出错原因：
	//    >display()为Point类public成员，Point3D以protected方式继承
	//    >所以该函数在Point3D类中是以protected型成员存在的，对外界不可见，所以Point3D
	//    >类的对象无法调用；
	
	//pt1.getX();
	//该语句执行出错原因：
	//    >getX()为Point类protected成员，Point3D以protected方式继承
	//    >该函数在Point3D中以protected型成员存在，对外界不可见，Point3D类的对象
	//    >无法调用
	
	//pt1._ix;
	//该语句执行出错原因：
	//    >_ix为基类Point的私有成员，派生类内部无法访问，派生类外部更无法访问
	
	return 0;
}
	

