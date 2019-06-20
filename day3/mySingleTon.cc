#include <iostream>
using std::cout;
using std::endl;

class SingleTon
{
	public:
		//创建对象函数
		static SingleTon* create()
		{
			if(pInstance==nullptr)//该类还没有创建对象
			{
				pInstance=new SingleTon();
				pInstance->_data=1;
				cout<<"创建新的对象"<<endl;			
			}else{
				cout<<"对象已被创建"<<endl;
			}
		return pInstance;
		}
		//销毁对象函数
		static void destroy()
		{
			if(pInstance!=nullptr)//该对象还未被销毁
			{
				delete pInstance;
				pInstance=nullptr;
				cout<<"对像销毁成功"<<endl;
			}else{
				cout<<"对象已被销毁过"<<endl;
			}
		}
		void print()
		{
			cout<<"print(),_data="<<_data<<endl;
		}
	private:
		//将构造析构函数隐藏起来使外界创建删除时失败，导致不能随意创建删除
		SingleTon()
		{
			cout<<"SingleTon()"<<endl;
		}
		~SingleTon()
		{
			cout<<"~SingleTon()"<<endl;
		}
	private:
			int _data;
			static SingleTon* pInstance;
};
//对静态数据成员初始化
SingleTon* SingleTon::pInstance=nullptr;

int main(void)
{
	SingleTon* p1=SingleTon::create();
	SingleTon* p2=SingleTon::create();

	SingleTon::create()->print();

	cout<<"p1="<<p1<<endl<<"p2="<<p2<<endl;

	p1->destroy();
	p2->destroy();


	//SingleTon s1;

	//delete &s1;
	//delete p1;
	
}

