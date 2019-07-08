#include <math.h>

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

//对比虚函数的动态多态的实现

//解耦
//基于对象的编程范式
//需求更直接，类的编写更灵活
class Figure
{
	public:
		//使用前一个名称代替后一个名称，类似于预处理 #define PI 3.14159
		using DisplayCallback=function<void()>;//函数对象类型 void f();
		using AreaCallback=function<double()>;//函数对象类型 double f();

		//设置Display回调函数
		void setDisplayCallback(DisplayCallback cb)//cb为void cb()类型
		{
			_cb1=cb;
		}
		
		//设置Area回调函数
		void setAreaCallback(AreaCallback cb)//cb为double cb()类型
		{
			_cb2=cb;
		}

		//执行Display回调函数
		void handleDisplayCallback()
		{
			if(_cb1){//_cb1不为空
				_cb1();//执行_cb1();
			}
		}

		//执行Area回调函数
		double handleAreaCallback()
		{
			if(_cb2){//_cb2不为空
				return _cb2();//执行_cb2()得到面积的值
			}else{//_cb2未被赋值
				return 0;
			}
		}
	private:
		//数据成员
		function<void()> _cb1;//_cb1类型为void _cb1();
		function<double()> _cb2;//_cb2类型为double _cb2();
};

//圆
class Circle
{
	public:
		//构造函数
		Circle(double radius)
		: _radius(radius)
		{}

		//打印函数 该函数类型为 void()
		void display() const
		{
			cout<<"circle";
		}

		//获得面积函数 该函数类型为 double()
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
{
	public:
		//构造函数
		Rectangle(double length,double width)
		: _length(length)
		, _width(width)
		{}

		//打印函数  函数类型 void()
		void print() const
		{
			cout<<"rectangle";
		}

		//获得面积函数 函数类型 double()
		double calcArea()
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
{
	public:
		//构造函数
		Triangle(double a,double b,double c)
		: _a(a)
		, _b(b)
		, _c(c)
		{}

		//打印函数 函数类型为 void()
		void show() const
		{
			cout<<"triangle";
		}

		//获得面积函数
		double getArea()
		{
			double p=(_a+_b+_c)/2;
			return sqrt(p*(p-_a)*(p-_b)*(p-_c));
		}

	private:
		//数据成员 三角形的三边
		double _a;
		double _b;
		double _c;
};

//立方体
class Cube
{
	public:
		//构造函数
		Cube(double a)
		: _a(a)
		{}

		//打印函数 函数类型 void()
		void display() const
		{
			cout<<"cube";
		}

		//获得面积函数 函数类型 double()
		double area()
		{
			return 6*_a*_a;
		}
	private:
		//数据成员
		double _a;//边长
};

void display(Figure & fig)//Figure类型对象的引用
{
	//执行回调函数
	fig.handleDisplayCallback();
	cout<<"的面积是："<<fig.handleAreaCallback()<<endl;
}

int main(void)
{
	//创建Figure类型的对象
	Figure fig;
	//创建其他类型的对象
	Circle circle(10);//圆对象
	Rectangle rectangle(20,30);//矩形对象
	Triangle triangle(3,4,5);//三角形对象
	Cube cube(10);//立方体对象
	
	//注册回调函数
	//bind将对象地址绑定到Circle类的成员函数中作为this指针，同时
	//bind返回一个void()类型的函数对象，将其赋值给Figure类对象fig
	//的数据成员_cb1
	fig.setDisplayCallback(std::bind(&Circle::display,&circle));
	//将bind返回的函数对象赋值给fig的数据成员_cb2
	fig.setAreaCallback(std::bind(&Circle::area,&circle));
	//执行回调函数
	display(fig);

	//将Rectangle类的打印函数赋值给fig的_cb1
	fig.setDisplayCallback(std::bind(&Rectangle::print,&rectangle));
	//将Rectangle类的获得面积函数赋值给fig的_cb2
	fig.setAreaCallback(std::bind(&Rectangle::calcArea,&rectangle));
	//执行回调函数
	display(fig);

	//将Triangle类的打印函数赋值给fig的_cb1
	fig.setDisplayCallback(std::bind(&Triangle::show,&triangle));
	//将Triangle类的获得面积函数赋值给fig的_cb2
	fig.setAreaCallback(std::bind(&Triangle::getArea,&triangle));
	//执行回调函数
	display(fig);

	//将Cube类的打印函数赋值给fig的_cb1
	fig.setDisplayCallback(std::bind(&Cube::display,&cube));
	//将Cube类的获得面积函数赋值给fig的_cb2
	fig.setAreaCallback(std::bind(&Cube::area,&cube));
	//执行回调函数
	display(fig);

	//非静态成员函数的第1个参数为自身类的this指针，所以在bind成员函数时
	//首先第1参数为指向该类的对象的指针。

	return 0;
}







































