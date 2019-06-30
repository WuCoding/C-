#include <iostream>
using std::cout;
using std::endl;

//面向抽象编程：
//    >只要接口不变，扩展随便实现

//开闭原则：
//    >对修改关闭，对扩展开放

//抽象类，定义了纯虚函数的类称为抽象类
class A
{
	public:
		//纯虚函数就是没有实现，只是作为接口存在
		virtual
		void display()=0;

		virtual
		void print()=0;

		//将析构函数设为虚函数
		virtual
		~A()
		{
			cout<<"~A()"<<endl;
		}
};

//抽象类的派生类
class B
: public A //以public方式继承
{
	public:
		//当一个类继承了抽象类之后，它必须实现所有的纯虚函数
		//如果有一个纯虚函数没有实现，该派生类也会成为抽象类
		//只实现了基类的display()纯虚函数，所以类B也是抽象类
		void display()
		{
			cout<<"B::display()"<<endl;
		}

		//析构函数，由于基类析构函数为虚函数，所以类B的析构函数
		//也为虚函数
		~B()
		{
			cout<<"~B()"<<endl;
		}
};

//抽象类B的派生类
class C
: public B //以public方式继承
{
	public:
		//类C中实现了print()纯虚函数，基类中的全部纯虚函数以实现，
		//类C不是抽象类
		//纯虚函数print()的实现
		void print()
		{
			cout<<"C::print()"<<endl;
		}

		//析构函数，因为基类析构函数设为虚函数，所以类C的析构函数
		//也为虚函数
		~C()
		{
			cout<<"~C()"<<endl;
		}
};

//打印函数
void display(A *pa)
{
	pa->display();//用基类抽象类A的指针调用display()函数，这里说明可以声明抽象类指针
}

int main(void)
{
	//A a;
	//该语句错误原因：
	//    >抽象类不能创建对象
	
	//B b;
	//该语句错误原因：
	//    >B类虽然实现了基类的纯虚函数，但并未全部实现，
	//    >所以B类也为抽象类
	
	//虽然抽象类不能创建对象，但可以用抽象类的指针
	
#if 1
	//创建一个C类对象
	C c;
	//抽象基类指针，指向一个派生类对象
	A *pa=&c;
	//通过基类指针来调用虚函数
	pa->display(); //调用类B中实现的纯虚函数display()函数
	pa->print();  //调用类C中实现的纯虚函数print()函数
#endif
	//基类指针指向一个堆内存上的类C的对象
	A *pa2=new C();
	//用基类指针调用虚函数
	pa2->display();//调用类B中实现的纯虚函数display()函数
	pa2->print();  //调用类C中实现的纯虚函数print()函数

	//通过基类指针删除一个堆内存上的派生类的对象
	delete pa2;//因为基类析构函数也被设为虚函数，所以调用的是派生类的析构函数
	           //然后先清除派生类数据，再清除基类部分数据，再清除基类的基类的
		   //部分的数据。

	return 0;
}



