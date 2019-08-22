#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

//单例对象自动释放
//方案3：具有平台相关性
//      atexit+pthread_once

class Singleton
{
	public:
		//创建单例对象函数
		static Singleton * getInstance()
		{
			//线程安全，该函数第一个参数为pthread_once_t类型，用宏定义来初始化
			//PTHREAD_ONCE_INIT，第二个参数为一个函数指针，表示在_once上只执行
			//1次init函数
			pthread_once(&_once,init);
			return _pInstance;
		}

		//初始化单例对象和注册atexit函数
		static void init()//该函数只在初始化时执行1次，所以被注册进pthread_once函数里
		{
			_pInstance=new Singleton();
			atexit(destroy);
		}

		//销毁单例对象函数，该函数不会主动调用，而是被atexit函数在程序结束之后主动调用
		static void destroy()
		{
			if(_pInstance!=nullptr)
			{
				delete _pInstance;
			}
		}

		//打印函数
		void print() const
		{
			cout<<"Singleton::print()"<<endl;
		}

	private:
		//构造和析构函数私有化
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
		static pthread_once_t _once;
};
//懒（饿）汉模式（懒加载），因为pthread_once是线程安全，所以可以用懒汉模式
Singleton * Singleton::_pInstance=nullptr;
//饱汉模式
//Singleton * Singleton::_pInstance=getInstance();

//初始化pthread_once_t类型
pthread_once_t Singleton::_once=PTHREAD_ONCE_INIT;

int main(void)
{
	Singleton * p1=Singleton::getInstance();
	p1->print();

	return 0;
}


