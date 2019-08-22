#include <iostream>
using std::cout;
using std::endl;

class Data
{
	public:
		//构造函数
		Data(int data=1)
		: _data(data)
		{
			cout<<"Data()"<<endl;
		}

		//打印函数
		void print() const
		{
			cout<<"_data="<<_data<<endl;
		}

		//析构函数
		~Data()
		{
			cout<<"~Data()"<<endl;
		}
	private:
		int _data;
};

class MiddleLayer//中间层类
{
	public:
		//构造函数
		MiddleLayer(Data * pdata)
		: _pdata(pdata)
		{
			cout<<"MiddleLayer(Data*)"<<endl;
		}

		//重构->运算符，返回Data类型的指针
		Data * operator->()
		{
			return _pdata;
		}

		//重构*运算符，返回Data类型的对象
		Data & operator*()
		{
			return *_pdata;
		}

		//析构函数
		~MiddleLayer()
		{
			cout<<"~MiddleLayer()"<<endl;
			//在析构函数中将Data类型的堆对象销毁
			if(_pdata!=nullptr)
			{
				delete _pdata;
				_pdata=nullptr;
			}
		}
	private:
		Data *_pdata;
};
//1.箭头运算符重载函数必须是类的成员函数
//2.指针运算符返回值必须是一个指针，或者是一个重载了箭头运算符的对象
//    >如果返回的是一个指针将调用内置的箭头运算符
//        >obj->data;==(*(obj.operator->())).data;
//        obj为重载了->运算符的类的对象，而不是指针
//        obj.operator->() 这个表达式是一个指针
//    >如果返回的是一个重载了->运算符的对象，则继续对该对象调用其重载
//    的箭头运算符，直到返回的是一个指针，再由该指针调用内置->运算符
//        >obj->data;==(*(obj.operator->().operator->())).data;
//        obj为重载了->运算符的类的对象，而不是指针
//        obj.operator->() 这个表达式依然是一个重载了->运算符的类的对象
//        obj.operator->().operator->() 这个才是一个指针，然后调用内置箭头运算符

class ThirdLayer//第三层类
{
	public:
		//构造函数
		ThirdLayer(MiddleLayer * pml)
		: _pml(pml)
		{
			cout<<"ThirdLayer(MiddleLayer*)"<<endl;
		}

		//重载->运算符，返回的是MiddleLayer类型对象
		MiddleLayer & operator->()
		{
			return *_pml;
		}

		//析构函数
		~ThirdLayer()
		{
			cout<<"~ThirdLayer()"<<endl;
			//将MiddleLayer类型的堆对象销毁
			if(_pml!=nullptr)
			{
				delete _pml;
				_pml=nullptr;
			}
		}
	private:
		MiddleLayer * _pml;//MiddleLayer类型的指针
};

int main(void)
{
	Data *pdata=new Data(12);
	pdata->print();//这是内置类型的箭头运算符
	(*pdata).print();
	delete pdata;
	cout<<endl;

	//智能指针的雏形
	MiddleLayer ml(new Data(10));//该对象是一个栈对象，在生命期结束时自动调用析构函数，将自动delete在堆内存上的Data类型的对象
	//接下来的用法形式上与指针无差别，但他却是一个栈空间对象
	ml->print();//这是简写，完整形式为(ml.operator->())->print();
	(*ml).print();
	cout<<endl;

#if 1
	ThirdLayer tl(new MiddleLayer(new Data(11)));
	tl->print();//简写，实际是Data类型的指针对Data类型成员函数的调用
#endif

	return 0;
}
	








































