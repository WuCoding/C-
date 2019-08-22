#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;

//普通函数
int add(int x,int y,int z)
{
	cout<<"int add(int,int,int)"<<endl;
	return x+y+z;
}

class Example
{
	public:
		//成员函数
		int add(int x,int y,int z)
		{
			cout<<"int Example::add(int,int,int)"<<endl;
			return _data+x+y+z;
		}

		//数据成员
		int _data=10;
};

void test0()
{
	//参数全部提前绑定
	auto f1=bind(add,1,10,20);
	cout<<"f1()="<<f1()<<endl;
	//实际执行 add(1,10,20)
	//显示：f1()=int add(int,int,int)
	//      31
	
	//占位符：不需要提前绑定的参数，需要使用占位符
	using namespace std::placeholders;
	//占位符的命名空间提前声明
	//占位符全称：std::placeholders::_1
	auto f2=bind(add,1,_3,_2);
	//此时表明只有函数调用时的第3和第2个实参是有效
	//其他所有实参都没有用
	cout<<"f2(2,3,4)="<<f2(2,3,4)<<endl;//这里只用到了3和4
	//实际执行 add(1,4,3)
	//显示：f2(2,3,4)=int add(int,int,int)
	//      8
}

void display(int n1,int n2,int n3,const int &n4,int n5)
{
	cout<<"("<<n1<<","<<n2<<","<<n3<<","<<n4<<","<<n5<<")"<<endl;
}

void test1()
{
	using namespace std::placeholders;
	int x=10,y=20;
	//bind提前绑定参数时采用的是值传递
	//占位符本身所在的位置是形参的位置，
	//占位符本身的数字代表的是函数调用时参数的位置
#if 0
	auto f=bind(display,_1,_2,x,std::cref(y),y);
	//引用需要加上std::cref，不加的话，虽然display的第4个参数为引用
	//但实际上还是值传递，结果为(111,112,10,20,20)
	//实际执行display(111,112,x,&y,y)，y的值改变，y的引用的值也改变
	//显示：(111,112,10,22,20)
#endif

#if 1
	//bind提前绑定参数之后，可以改变函数类型
	std::function<void(int,int)> f=bind(display,_1,_2,x,std::cref(y),y);
	//f函数的类型为void f(int,int)
	//注意引用需要加上std::cref，不然就是值传递
	//实际执行display(111,112,x,&y,y)，y的值改变，y的引用的值也改变
	//显示：(111,112,10,22,20)
#endif	

	//display函数的第4个参数为引用形式，此时将y值改变，观察结果
	y=22;
	//虽然很多参数，编译时不会报错并且可以执行，但是除了第1和第2个参数
	//其他参数全都无效
	//f(111,112,333,1,2,3,4,5,6);
	f(111,112);
	//当f类型为std::function<void(int,int)>类型时，执行f(111,112,333,1,2,3,4,5,6)
	//就会报错，因为类型已经限定了只有两个参数
}

void test2()
{
	using namespace std::placeholders;
	std::function<int(int,int)> f=bind(add,_1,_2,100);
	//f函数的类型为 int f(int,int)
	cout<<"f(1,2)="<<f(1,2)<<endl;
	//实际执行add(1,2,100)
	//显示：f(1,2)=int add(int,int,int)
	//     103

	{
		//将一个自定义类型的对象作为一个局部对象
		Example e;
		//成员函数作为bind的第1个参数时要加类型限定和取地址
		f=bind(&Example::add,&e,_1,200,_2);
		//对象以地址传入，作为this指针，每个非静态成员函数
		//调用时第1参数都为一个对象的this指针
		cout<<"f(1,2)="<<f(1,2)<<endl;
		//实际执行e.add(1,200,2)，对象e的数据成员_data为10
		//显示：f(1,2)=int Example::add(int,int,int)
		//       213
	}

	//cout<<"f(1,2)="<<f(1,2)<<endl;
	//该语句执行出错原因：指定的对象已经被销毁了，使用会出问题
	
	//对于成员函数而言，绑定的第一个参数就是this指针，
	//提前绑定时，可以传递指针，也可以传递对象
	Example e;
	f=bind(&Example::add,e,_1,200,_2);//传递对象
	cout<<"f(1,2)="<<f(1,2)<<endl;
	//实际执行e.add(1,200,2)，对象e的数据成员_data=10
	//显示：f(1,2)=int Example::add(int,int,int)
	//      213
}

int main(void)
{
	//test0();
	//test1();
	test2();

	return 0;
}
