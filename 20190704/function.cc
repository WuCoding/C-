#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

//函数类型为 void()
void display()
{
	cout<<"display()"<<endl;
}

void print()
{
	cout<<"print()"<<endl;
}

//pointer为函数指针
void (*pointer)()=display;
//预处理语句
typedef void(*Function)();//Function表示void()函数类型

//用C语言表达多态的特性
void test0()
{
	pointer();//调用函数指针

	Function f=display;//用普通函数注册回调函数

	f();//执行回调函数

	f=print;//用函数指针注册回调函数
	
	f();//执行回调函数
}

//function<>相当于函数容器
void FunctionCall(function<void()> f)
{
	f();//执行回调函数
}

//类中成员函数
class Example
{
	public:
		void display() const
		{
			cout<<"Example::display()"<<endl;
		}
};

void test1()
{
	FunctionCall(display);
	//显示：display()
	FunctionCall(print);
	//显示：print()
	//FunctionCall(Example::display);
	//该语句执行出错，因为非静态成员函数的调用会自动传递对象地址作为
	//this指针，而FuctionCall中执行的回调函数为无参类型
}

void test2()
{
	//std::function函数的容器，可以容纳某一种函数类型的函数
	//函数形式可以是任意形式
	//    >普通函数
	//    >函数指针
	//    >成员函数
	
	Function f=print;//Function为void()函数类型，f为函数指针
	function<void()> f1=display;
	//执行回调函数
	f1();
	//显示：display()
	//用函数指针来注册回调函数
	f1=f;
	//执行回调函数
	f1();
	//显示：print()

	//成员函数来注册回调函数
	Example e;
	f1=std::bind(&Example::display,&e);
	//f1为绑定了对象地址（this指针）的成员函数
	//执行回调函数
	f1();
	//显示：Example::display()
}

int main(void)
{
	//test1();
	test2();

	return 0;
}
