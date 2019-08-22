#include <iostream>
using std::cout;
using std::endl;

template <class T>
class Singleton
{
	class AutoRelease //自动释放单例类型对象
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
				if(_pInstance){ //如果_pInstance不为空，即单例对象存在
					delete _pInstance;
					_pInstance=nullptr;
					cout<<"~AutoRelease()"<<endl;
				}
			}
	};

	public:
	//虽然类模板中只有一个class T类型参数，但该成员函数模板却有多个类型参数
	template<class...Args>
	static T* getInstance(Args...args) //参数包
	{
		if(nullptr==_pInstance){ //对象未创建
			(void)_auto; //这样才会创建一个AutoRelease类型对象，
				     //调用该类的构造函数，否则将不会创建_auto对象（不知道为啥）
			_pInstance=new T(args...);
		}
		return _pInstance;
	}
	private:
	//将构造和析构函数私有化
	Singleton(){}
	~Singleton(){}
	private:
	//数据成员
	static T *_pInstance; //指向堆空间对象的指针
	static AutoRelease _auto; //自动释放单例对象的类型对象，需要放在静态区
};

//类外初始化静态数据成员
template<class T>
T* Singleton<T>::_pInstance=nullptr;

template<class T>
typename Singleton<T>::AutoRelease Singleton<T>::_auto;
//要用typename来告诉编译器Singleton<T>::AutoRelease是一个类型

//自定义类型
class Point
{
	public:
		//构造函数
		Point(int ix=0,int iy=0)
		: _ix(ix)
		, _iy(iy)
		{
			cout<<"Point(int,int)"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"("<<_ix<<","<<_iy<<")"<<endl;
		}

		//析构函数
		~Point()
		{
			cout<<"~Point()"<<endl;
		}

	private:
		//数据成员
		int _ix;
		int _iy;
};

int main(void)
{
	Point *p1=Singleton<Point>::getInstance(1,2);
	//显示：AutoRelease()
	//	Point(int,int)
	Point *p2=Singleton<Point>::getInstance(3,4);

	p1->print();
	//显示：(1,2)
	p2->print();
	//显示：(1,2)
	cout<<"p1="<<p1<<endl<<"p2="<<p2<<endl;
	//显示：p1=0x55eb13634280
	//	p2=0x55eb13634280

	Point pt(3,4);
	//显示：Point(int,int)
	
	pt.print();
	//显示：(3,4)
	
	//显示：~Point()
	//	~Point()
	//	~AutoRelease()
	return 0;
}

