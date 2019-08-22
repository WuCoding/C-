#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;

//类的前置声明
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

		//数据成员，智能指针
		shared_ptr<Parent> _pParent;
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

		//数据成员，智能指针
		shared_ptr<Child> _pChild;
};

//问题：shared_ptr的循环引用会导致内存泄露
//解决方案：weak_ptr

int main(void)
{
	shared_ptr<Parent> pParent(new Parent());
	//显示：Parent()
	shared_ptr<Child> pChild(new Child());
	//显示：Child()

	//你中有我，我中有你
	pParent->_pChild=pChild;
	pChild->_pParent=pParent;

	//显示两个智能指针的引用计数
	cout<<"parent's use_count="<<pParent.use_count()<<endl;
	//显示：parent's use_count=2
	cout<<"child's use_count="<<pChild.use_count()<<endl;
	//显示：child's use_count=2

	return 0;

	//并未显示析构函数的执行，内存泄漏
}

