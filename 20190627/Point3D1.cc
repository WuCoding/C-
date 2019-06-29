#include <iostream>
using std::cout;
using std::endl;
//派生类只能访问基类的非private成员，从基类获得的成员权限为：派生类继承方式和该成员在基类的权限的交集
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

	protected://该权限内容只对派生类内部开放，同时对外部是不可见的
		int getX() const
		{
			return _ix;
		}
		int _iy;
	private:
		int _ix;
};

class Point3D
: public Point //以public形式继承，接口继承
{
	public:
		//构造函数
		Point3D(int ix,int iy,int iz)
		: Point(ix,iy) //主动用基类的构造函数来初始化基类数据成员
		, _iz(iz)      //初始化派生类自己的数据成员
		{
			cout<<"Point(int,int,int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			//派生类内部不能访问基类的私有成员
			//cout<<_ix;  这句话是错的，_ix是基类的private成员，对派生类内部来说是不可见的
			cout<<"("<<getX()<<","<<_iy<<","<<_iz<<")"<<endl;
			//虽然_ix对派生类内部不可见，但可通过基类对外的接口getX()函数来获得_ix的值，
			//getX()函数在基类中是protect成员，对派生类内部是可见的
		}

	private:
		int _iz;
};

int main(void)
{
	Point3D pt1(1,2,3);
	pt1.display();
	//display()在基类中为public成员，基类Point3D是public方式继承，所以display()在
	//派生类Point3D中依然是public成员，所以派生类的对象是可以访问display()成员函数的
	
	
	//pt1.getX();
	//getX()是Point类的protected成员，Point3D类是public继承方式，所以getX()在Point3D类里也是protected成员，外界是无法访问到的，Point3D类的对象是无法调用该函数的
	
	
	//pt1._ix;
	//_ix是基类的数据成员位于private，对于派生类内部是不可访问的，派生类的对象更不能访问到
	
	return 0;
}


