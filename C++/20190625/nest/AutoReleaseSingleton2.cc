#include <iostream>
using std::cout;
using std::endl;

//单例对象自动释放
//方案2：atexit+静态方法

class Singleton
{
	public:
		//单例对象的创建
		static Singleton *getInstance()
		{
			//在多线程环境下是非线程安全的
			//加锁
			if(_pInstance==nullptr){
				//new表达式执行分两步：1. new堆空间。2. 执行构造函数。
				_pInstance=new Singleton();
				//在初次创建对象时就注册atexit方法，这样可以之注册1次，避免了double free的情况
				atexit(destroy);
			}
			return _pInstance;
		}

		//单例对象的销毁
		static void destroy()
		{
			if(_pInstance!=nullptr)
			{
				//delete表达式执行分两步：1.执行析构函数。2.delete堆空间
				delete _pInstance;
			}
		}

		//打印函数
		void print() const
		{
			cout<<"Singleton::print()"<<endl;
		}

	private:
		//将构造和析构函数私有化
		Singleton()
		{
			cout<<"Singleton()"<<endl;
		}
		~Singleton()
		{
			cout<<"~Singleton()"<<endl;
		}
	private:
		//数据成员
		static Singleton * _pInstance;
};
//懒（饿）汉模式（懒加载）
//Singleton * Singleton::_pInstance=nullptr;
//饱汉模式，在进入main函数之前，也就是线程启动之前就先创建对象，解决多线程安全问题
Singleton * Singleton::_pInstance=getInstance();

int main(void)
{
	Singleton * p1=Singleton::getInstance();
	p1->print();

	//Singleton::destroy(); 不需要主动调用销毁对象函数，程序结束时会自动执行atexit注册的对象销毁函数
	return 0;
}
