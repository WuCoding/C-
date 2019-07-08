#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

//----------------------------重新复习一下虚函数---------------------------
//抽象类
class Figure
{
	public:
		//纯虚函数
		virtual void display() const=0;
		virtual double area()=0;
};

//圆
class Circle
: public Figure //以public方式继承抽象类
{
	public:
		//构造函数
		Circle(double radius)
		: _radius(radius)
		{}

		//打印函数
		void display() const
		{
			cout<<"circle";
		}

		//返回面积函数
		double area()
		{
			return 3.14159*_radius*_radius;
		}
	private:
		//数据成员
		double _radius;//半径
};

//矩形
class Rectangle
: public Figure //以public方式继承抽象类
{
	public:
		//构造函数
		Rectangle(double length,double width)
		: _length(length)
		, _width(width)
		{}

		//打印函数
		void display() const
		{
			cout<<"rectangle";
		}

		//返回面积
		double area()
		{
			return _length*_width;
		}
	private:
		//数据成员
		double _length;//长
		double _width;//宽
};

//三角形
class Triangle
: public Figure //以public方式继承抽象类
{
	public:
		//构造函数
		Triangle(double a,double b,double c)
		: _a(a)
		, _b(b)
		, _c(c)
		{}

		//打印函数
		void display() const
		{
			cout<<"triangle";
		}

		//返回面积函数
		double area()
		{
			double p=(_a+_b+_c)/2;
			return sqrt(p*(p-_a)*(p-_b)*(p-_c));
		}
	private:
		//数据成员，三角形三边长
		double _a;
		double _b;
		double _c;
};

//立方体
class Cube
: public Figure
{
	public:
		//构造函数
		Cube(double a)
		: _a(a)
		{}

		//打印函数
		void display() const
		{
			cout<<"Cube";
		}

		//返回面积函数
		double area()
		{
			return 6*_a*_a;
		}
		
	private:
		//数据成员
		double _a;//边长
};

//打印函数，形参类型为基类的指针
void display(Figure *fig)
{
	fig->display();//基类型指针调用虚函数，触发动态多态机制
	cout<<"的面积是："<<fig->area()<<endl;
}

int main(void)
{
	//创建派生类的对象
	Circle circle(10);
	Rectangle rectangle(20,30);
	Triangle triangle(3,4,5);
	Cube cube(10);

	//执行打印函数，触发动态多态特性
	display(&circle);
	display(&rectangle);
	display(&triangle);
	display(&cube);

	return 0;
}

	



