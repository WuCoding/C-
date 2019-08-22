#include <string.h>
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

//只能生成栈对象，不能生成堆对象
//解决方案：将operator new放入private区域中
//这样外界就无法使用new表达式，也就无法在堆内存中申请空间了

class Student
{
	public:
		//构造函数
		Student(int id,const char *name)
		: _id(id)
		, _name(new char[strlen(name)+1]())
		{
			strcpy(_name,name);
			cout<<"Student(int,const char*)"<<endl;
		}
		void print() const
		{
			cout<<"("<<_id<<","<<_name<<")"<<endl;
		}
		//析构函数
		~Student()
		{
			delete [] _name;
			cout<<"~Student()"<<endl;
		}
	private:
		//因为只是将重构的 new 和 delete 封起来，并不会用到，所以只写声明就可以，不需要写实现
		//因为 new 和 delete 使用时与单个的对象无关，所以用static使所有对象都能访问
		static void* operator new(size_t sz);
		static void operator delete(void* pointer);
	private:
		int _id;
		char *_name;
};
//只能生成栈对象不能生成堆对像
int main(void)
{
	Student s1(101,"John");
	s1.print();

	return 0;
}
