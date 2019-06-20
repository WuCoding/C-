#include <iostream>
using std::cout;
using std::endl;

class NullPtrCall
{
	public:
		void func1()
		{
			cout<<"func1()"<<endl;
		}

		void func2(int ix)
		{
			cout<<"func2() ix="<<ix<<endl;
		}

		static void func3()
		{
			cout<<"func3()"<<endl;
		}

		void func4()
		{
			cout<<"func4() _ix"<<this->_ix<<endl;
		}
	private:
		int _ix;
};

int main(void)
{
	NullPtrCall *p=nullptr;

	p->func1();//真实调用过程 NullPtrCall::func1(nullptr);没有影响
	p->func2(10);//NullPtrCall::func2(nullptr,10); 没有影响
	p->func3();//NullPtrCall::func3();因为静态成员函数没有this指针
	p->func4();//NullPtrCall::func4(nullptr);会发生段错误，因为发生了this->_ix,但this为nullptr,对一个空指针解引用，发生错误
	
	return 0;
}
