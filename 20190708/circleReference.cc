#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

class Parent;

class Child
{
	public:
		//构造函数
		Child()
		{
			cout<<"Child()"<<endl;
		}

		//析构函数
		~Child()
		{
			cout<<"~Child()"<<endl;
		}

		//weak_ptr智能指针托管
		weak_ptr<Parent> _pParent;
};

class Parent
{
	public:
		//构造函数
		Parent()
		{
			cout<<"Parent()"<<endl;
		}

		//析构函数
		~Parent()
		{
			cout<<"~Parent()"<<endl;
		}

		//shared_ptr智能指针托管
		shared_ptr<Child> _pChild;
};
//用weak_ptr来解决循环引用导致的内存泄露问题

int main(void)
{
	shared_ptr<Parent> pParent(new Parent());
	//显示：Parent()
	shared_ptr<Child> pChild(new Child());
	//显示：Child()

	pParent->_pChild=pChild;//shared_ptr=shared_ptr; 引用计数+1
	pChild->_pParent=pParent;//weak_ptr=shared_ptr;  引用计数+1，保持不变

	cout<<"parent's use_count="<<pParent.use_count()<<endl;
	//显示：parent's use_count=1
	cout<<"child's use_count="<<pChild.use_count()<<endl;
	//显示：child's use_count=2

	return 0;
	//显示：~Parent()
	//	~Child()
}
