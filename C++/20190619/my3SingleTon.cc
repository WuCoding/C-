#include <iostream>
using std::cout;
using std::endl;
//SingleTon

class SingleTon
{
	public:
		static SingleTon* create()
		{
			if(_pInstance!=nullptr)
			{
				cout<<"Instance is exist"<<endl;
				return _pInstance;
			}
			_pInstance=new SingleTon();
			cout<<"create Instance success"<<endl;
			return _pInstance;

		}
		static void destroy()
		{
			if(_pInstance==nullptr)
			{
				cout<<"Instance is not exist"<<endl;
				return;
			}
			delete _pInstance;
			_pInstance=nullptr;
			cout<<"delete success"<<endl;
			return;
		}
		void print() const
		{
			cout<<"data="<<this->_data<<endl;
		}
	private:
		SingleTon()
		: _data(0)
		{
			cout<<"SingleTon()"<<endl;
		}
		~SingleTon()
		{
			cout<<"~SingleTon()"<<endl;
		}
	private:
		int _data;
		static SingleTon* _pInstance;
};
SingleTon* SingleTon::_pInstance=nullptr;

int main(void)
{
	//stack
	//SingleTon st;
	//st.print();
	//heap
	SingleTon *p1=SingleTon::create();
	p1->print();

	SingleTon *p2=SingleTon::create();
	p2->print();

	cout<<"p1="<<p1<<endl
		<<"p2="<<p2<<endl;

	SingleTon::create()->print();

	cout<<"SingleTon::create()="<<SingleTon::create()<<endl;

	p1->destroy();
	p2->destroy();


	return 0;
}
