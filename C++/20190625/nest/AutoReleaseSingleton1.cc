#include <iostream>
using std::cout;
using std::endl;

//单例对象自动释放
//方案1：嵌套类+静态对象

class Singleton
{
	//嵌套类，可以访问外壳类的私有成员，此处即Singleton类的私有成员
	class AutoRelease
	{
		public:
			//构造函数
			AutoRelease()
			{
				cout<<"AutoRelease()"<<endl;
			}
			//析构函数
			~AutoRelease()
			{
				if(_pInstance!=nullptr){//嵌套类可以访问Singleton类的私有成员
					delete _pInstance;
					_pInstance=nullptr;
					cout<<"~AutoRelease()"<<endl;
				}
			}
	};

	public:
		//创建对象函数
		static Singleton *getInstance()
		{
			//在多线程环境下是非线程安全的，因为可能同时有多个线程进入if语句，进行new操作
			//但是只能返回一个地址，另一个地址在新地址赋给_pInstance后就被覆盖了，造成内
			//存泄露
			//加锁
			if(_pInstance==nullptr)
			{
				_pInstance=new Singleton();
			}
			return _pInstance;
		}

		//销毁对象函数
		static void destroy()
		{
			if(_pInstance!=nullptr)
			{
				delete _pInstance;
				_pInstance=nullptr;
			}
		}

		//打印函数
		void print() const
		{
			cout<<"Singleton::print()"<<endl;
		}
	private:
		//构造函数私有化
		Singleton()
		{
			cout<<"Singleton()"<<endl;
		}

		//析构函数私有化
		~Singleton()
		{
			cout<<"~Singleton()"<<endl;
		}
	private:
		static Singleton *_pInstance;//单例对象的堆内存指针
		static AutoRelease _autoRelease;//自动销毁单例对象AutoRelease类的对象，位于全局静态区，如果去掉static，则该对象位于堆内存上，此时只有单例对象释放堆内存空间时，才会执行AutoRelease类型的析构函数，这样就失去了该类的意义，所以将该对象放在全局静态区
};

//懒（饿）汉模式 （懒加载），懒汉模式在多线程中不安全
//Singleton * Singleton::_pInstance=nullptr;
//饱汉模式，解决多线程安全的的问题，在进入main函数之前就先将对象创建出来
Singleton * Singleton::_pInstance=getInstance();
//静态数据成员在类外初始化
Singleton::AutoRelease Singleton::_autoRelease;
//不要写成Singleton::AutoRelease Singleton::_autoRelease();有的人想这样的话就是调用无参构造函数，但编译器会把这个当成一个函数的声明
//例：int a(); 这并不是初始化int型变量a的意思，而是一个返回值为int型名字为a的无参函数的声明

int main(void)
{
	Singleton *p1=Singleton::getInstance();
	p1->print();

	//Singleton::destroy(); 不需要直接调用销毁函数，单例对象的销毁直接由AutoRelease类型的析构函数自动执行
	return 0;
}







































