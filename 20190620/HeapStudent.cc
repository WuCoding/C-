#include <string.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

//要求：只生成堆对象，不能生成栈对象 Student * pstu=new Student();可以 Student stu;不可以
//解决方案：
//将析构函数放入private区域，这样栈对象销毁时，自动调用析构函数会导致失败，而可以为堆对象构造一个destroy方法销毁函数，在destroy方法中去执行delete表达式，delete表达式执行之前会先调用析构来回收对象数据资源

class Student
{
	public:
		//构造函数
		Student(int id,const char *name)
		: _id(id)
		, _name(new char [strlen(name)+1]())
		{
			strcpy(_name,name);
			cout<<"Student(int id,const char *name)"<<endl;
		}

		void print() const
		{
			cout<<"("<<_id<<","<<_name<<")"<<endl;
		}
		//提供一个接口，可以自定义开辟空间的方式
		//放在类内部，只对Student类型起作用
		//放在类之外，对所有的类型都会起作用
		
		//重构new运算符
		static void *operator new(size_t sz)
		{
			cout<<"void * operator new(size_t)"<<endl;
			return malloc(sz);//在堆内存上开辟一个空间返回头指针
		}

		//重构delete运算符
		static void operator delete(void* pointer)
		{
			cout<<"void operator delete(void*)"<<endl;
			free(pointer);
		}

		//为堆对象构造的销毁函数
		void destroy()
		{
			//其实delete运算符执行的过程分为两步，先执行this->~Student();
			//再执行delete语句
			delete this;
		}
	private:
		~Student()
		{
			delete [] _name;//释放对象数据成员占用的资源
			cout<<"~Student()"<<endl;
		}
	private:
		int _id;
		char *_name;
};

int main(void)
{
	Student * pstu=new Student(100,"Jackie");//new语句也分为两步，第一执行new语句在堆空间上开辟空间，第二步调用构造函数
	pstu->print();
	//delete pstu; 这条语句是错误的，因为执行delete语句会先执行析构函数，而析构函数对外界不可见，所以调用失败
	pstu->destroy();//destroy()方法中执行delete语句，在执行delete语句之前会先执行析构函数，而此时destroy是类内部的成员函数，可以访问类中的数据成员，也就可以调用析构函数
	return 0;
}



