#include <iostream>
using std::cout;
using std::endl;

class SingleTon
{
	public:
		//创建对象函数
		static SingleTon* create()
		{
			if(_pInstance==nullptr)
			{
				_pInstance=new SingleTon();
				_pInstance->_data=10;
				cout<<"创建新对象成功"<<endl;
			}else{
				cout<<"对象已存在，请勿重复创建"<<endl;
			}
			return _pInstance;
		}
		//销毁对象函数
		static void destroy()
		{
			if(_pInstance!=nullptr)
			{
				delete _pInstance;
				cout<<"删除对象成功"<<endl;
				_pInstance=nullptr;
			}else{
				cout<<"要删除的对象不存在，删除失败"<<endl;
			}
		}

		void print()
		{
			cout<<"data="<<_data<<endl;
		}
	private:
		SingleTon()
		: _data(0)
		{
			cout<<"SingTon()"<<endl;
		}
		~SingleTon()
		{
			cout<<"~SingTon()"<<endl;
		}
	private:
		int _data;
		static SingleTon* _pInstance;
};
SingleTon* SingleTon::_pInstance=nullptr;

int main(void)
{
	SingleTon *p1=SingleTon::create();
	p1->print();
	SingleTon *p2=SingleTon::create();
	p2->print();

	cout<<"p1="<<p1<<endl
		<<"p2="<<p2<<endl;
	p1->destroy();
	p2->destroy();

	return 0;
}

