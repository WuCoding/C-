#include <iostream>
using std::cout;
using std::endl;

//要求：通过某一个类在内存中只能创建唯一的一个对象
//1.该对象不能是栈（全局）对象
//2.该对象只能是一个堆对象


class SingleTon
{
	public:
		//创建对象函数
		static SingleTon* getInstance()
		{
			if(_pInstance==nullptr){//如果对象还没有创建则在堆空间开辟空间
				_pInstance=new SingleTon();
			}
			return _pInstance;
		}
		//销毁对象函数
		static void destroy()
		{
			if(_pInstance){//如果还没有被销毁（不为nullptr），则进行销毁，防止重复销毁
				delete _pInstance;
			}
		}
		//只要不改变对象数据成员的都设为const这样const对象和非const对象都可以使用
		void print() const
		{
			cout<<"SingleTon::data="<<_data<<endl;
		}
	private:
		//这里其实并没有用到构造和析构函数只是为了不用系统的默认构造析构（系统默认的是public的），然后将构造析构放进这里不让外界访问
		//为了不能随意创建，将构造函数设为private，只有类内可以访问
		SingleTon()
		: _data(0)
		{
			cout<<"SingleTon()"<<endl;
		}
		//为了不能随便删除，将析构函数也放进private中，类外不能访问，只能通过类对外的接口来判断是否要调用构造和析构
		~SingleTon()
		{
			cout<<"~SingleTon()"<<endl;
		}
	private:
		//数据成员
		int _data;
		//静态数据成员，用来存对象地址，同时被静态函数访问
		static SingleTon *_pInstance;
};
//对静态数据成员在全局位置进行初始化
SingleTon * SingleTon::_pInstance=nullptr;
int main(void)
{
	//SingleTon s1; 因为构造函数被放到了private中所以创建失败
	
	//SingleTon *p=new SingleTon();  这里也用到了构造函数，所以也会失败

	SingleTon *p1=SingleTon::getInstance();//通过该接口来创建对象
	SingleTon *p2=SingleTon::getInstance();//再次创建
	
	SingleTon::getInstance()->print();

	//打印两个对像的地址，会发现都是一个地址，即一个对象
	cout<<"p1="<<p1<<endl
		<<"p2="<<p2<<endl;

	//delete p1; 因为析构函数放在private中，所以该语句会执行失败
	
	//调用函数public的静态函数成员来销毁对象
	
	SingleTon::destroy();
	
	return 0;
}








