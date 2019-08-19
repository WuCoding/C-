#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

//抽象类
class Figure
{
public:
	//纯虚函数
	virtual void display() const=0;
	virtual double area()=0;
};

class Circle
: public Figure
{
public:
	//构造函数
	Circle(double radius)
	: _radius(radius)
	{}

	//展示函数，虚函数
	void display() const
	{
		cout<<"circle";
	}

	//求面积函数，虚函数
	double area()
	{
		return 3.14159*_radius*_radius;
	}
private:
	double _radius;
};

class Rectangle
: public Figure
{
public:
	//构造函数
	Rectangle(double length,double width)
	: _length(length)
	, _width(width)
	{}

	void display() const
	{
		cout<<"rectangle";
	}

	double area()
	{
		return _length *_width;
	}
private:
	//数据成员
	double _length;
	double _width;
};

class Triangle
: public Figure
{
public:
	//构造函数
	Triangle(double a,double b,double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{}

	void display() const 
	{
		cout<<"triangle";
	}

	double area()
	{
		double p=(_a+_b+_c)/2;
		return sqrt(p*(p-_a)*(p-_b)*(p-_c));
	}
private:
	//数据成员
	double _a;
	double _b;
	double _c;
};

class Cube
: public Figure
{
public:
	//构造函数
	Cube(double a)
	: _a(a)
	{}

	void display() const
	{
		cout<<"cube";
	}

	double area()
	{
		return 6*_a*_a;
	}

private:
	double _a;
};

void display(Figure *fig)
{
	fig->display();
	cout<<"的面积是："<<fig->area()<<endl;
}

//静态工厂方法
//缺点：
//	1.不满足开闭原则
//	2.不满足单一职责原则
class Factory
{
public:
	static Circle createCircle()
	{
		//load xml
		//....
		Circle circle(10);
		return circle;
	}

	static Rectangle createRectangle()
	{
		//load xml
		//....
		Rectangle rectangle(20,30);

		return rectangle;
	}

	static Triangle createTriangle()
	{
		//load xml
		//....
		Triangle triangle(3,4,5);

		return triangle;
	}

};

int main(void)
{
	Circle circle=Factory::createCircle();
	Rectangle rectangle=Factory::createRectangle();
	Triangle triangle=Factory::createTriangle();

	display(&circle);
	display(&rectangle);
	display(&triangle);

	Cube cube(10);
	display(&cube);

	return 0;
}








