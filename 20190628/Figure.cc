#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

//抽象类，只要类中含有一个纯虚函数，该类便为抽象类，抽象类
//只能作为基类来派生新类，不能创建抽象类的对象，但可声明
//抽象类的指针
class Figure
{
	public:
		//纯虚函数，纯虚函数不能被直接调用，仅提供一个
		//与派生类一致的接口
		virtual void display() const=0;//打印函数
		virtual double area()=0;//面积函数
};

//只有在派生类中给出了基类中所有纯虚函数的实现，该派生类
//便不再是抽象类，否则该派生类依然是抽象类

//以抽象类为基类的派生类
//----------------------------------------圆形-------------------------------------------
class Circle
: public Figure //以public方式继承
{
	public:
		//构造函数
		Circle(double radius)
		: _radius(radius)
		{}

		//基类中<打印函数>纯虚函数的实现
		void display() const
		{
			cout<<"circle";
		}

		//基类中的<求面积函数>纯虚函数的实现
		double area()
		{
			return 3.14159*_radius*_radius;
		}

	private:
		//数据成员<半径>
		double _radius;
};

//派生类
//----------------------------------------矩形-----------------------------------------------
class Rectangle
: public Figure  //以public方式继承
{
	public:
		//构造函数
		Rectangle(double length,double width)
		: _length(length)
		, _width(width)
		{}
		
		//基类<打印函数>纯虚函数的实现
		void display() const
		{
			cout<<"rectangle";
		}

		//基类的<求面积函数>纯虚函数的实现
		double area()
		{
			return _length*_width;
		}
	private:
		  //数据成员<长、宽>
		  double _length;
		  double _width;
};

//派生类
//---------------------------------------------三角形--------------------------------------------
class Triangle
: public Figure //以public方式继承
{
	public:
		//构造函数
		Triangle(double a,double b,double c)
		: _a(a)
		, _b(b)
		, _c(c)
		{}

		//基类<打印函数>纯虚函数实现
		void display() const
		{
			cout<<"triangle";
		}
		
		//基类<求面积函数>纯虚函数的实现
		double area()
		{
			double p=(_a+_b+_c)/2;
			return sqrt(p*(p-_a)*(p-_b)*(p-_c));
		}
	private:
		//数据成员<三角形三边长>
		double _a;
		double _b;
		double _c;
};

//派生类
//----------------------------------------------立方体-------------------------------------------
class Cube
: public Figure //以public方式继承
{
	public:
		//构造函数
		Cube(double a)
		: _a(a)
		{}

		//基类<打印函数>纯虚函数的实现
		void display() const
		{
			cout<<"cube";
		}

		//基类<求面积函数>纯虚函数的实现
		double area()
		{
			return 6*_a*_a;
		}
	private:
		//数据成员<边长>
		double _a;
};

//打印形状名称和面积
void display(Figure *fig)
{
	fig->display(); //动态多态触发机制，基类指针调用虚函数
	cout<<"的面积是："<<fig->area()<<endl;
}

int main(void)
{
	//圆形对象
	Circle circle(10);
	//矩形对象
	Rectangle rectangle(20,30);
	//三角形对象
	Triangle triangle(3,4,5);
	//立方体对象
	Cube cube(10);

	//打印圆形对象信息
	display(&circle);
	//打印矩形对象信息
	display(&rectangle);
	//打印三角形对象信息
	display(&triangle);
	//打印立方体信息
	display(&cube);

	return 0;
}



































