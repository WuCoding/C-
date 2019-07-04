#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//类模板
template <class Type,int kSize=10>
class Stack
{
	public:
		//构造函数
		Stack()
		: _top(-1)
		, _base(new Type[kSize]())
		{}

		//析构函数
		~Stack();

		//判断栈满
		bool full() const;
		//判断栈空
		bool empty() const;
		//压栈操作
		void push(const Type &value);
		//出栈操作
		void pop();
		//返回栈顶元素
		const Type & top() const;
	private:
		//数据成员
		int _top; //栈顶元素下标
		Type *_base; //堆空间数组地址
};
//-----------------------------------------类成员函数的实现----------------------------------------
//析构函数的实现
template <class Type,int kSize>//一定要在函数实现前写上该句
Stack<Type,kSize>::~Stack() //类名限定要类名后加上<Type,kSize>
{
	if(_base){//_base不为nullptr
		delete [] _base;
		_base=nullptr;
	}
}

//判断栈满函数实现
template <class Type,int kSize>
bool Stack<Type,kSize>::full() const
{
	return _top==kSize-1;
}

//判断栈空函数实现
template <class Type,int kSize>
bool Stack<Type,kSize>::empty() const
{
	return _top==-1;
}

//压栈操作函数实现
template <class Type,int kSize>
void Stack<Type,kSize>::push(const Type &value)
{
	if(!full()){//栈不满
		_base[++_top]=value;
	}else{//栈满
		cout<<"stack is full,cannot push any more data!"<<endl;
	}
}

//出栈操作函数实现
template <class Type,int kSize>
void Stack<Type,kSize>::pop()
{
	if(!empty()){//栈不空
		--_top;
	}else{//栈空
		cout<<"stack is empty, no more data!"<<endl;
	}
}

//返回栈顶元素
template <class Type,int kSize>
const Type &Stack<Type,kSize>::top() const
{
	return _base[_top];
}
//---------------------------------------类成员函数实现完毕----------------------------------
int test0()
{
	Stack<int> stack;
	cout<<">>此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？1
	//将1压入栈中
	stack.push(1);
	cout<<">>此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？0

	//将2~11压入栈中
	for(int idx=2;idx!=12;++idx)
	{
		stack.push(idx);
	}
	//显示：stack is full,cannot push any more data!
	
	cout<<">> 此时栈中是否已满？"<<stack.full()<<endl;
	//显示：>>此时栈中是否已满？1
	
	while(!stack.empty()){//栈不为空时进入循环
		//打印栈顶元素
		cout<<stack.top()<<endl;
		//将栈顶元素出栈
		stack.pop();
	}
	//显示：10
	//      9
	//      8
	//      7
	//      6
	//      5
	//      4
	//      3
	//      2
	//      1
	
	cout<<">> 此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？1

	return 0;
}

int test1()
{
	//因为在c++中string类型也为内置类型，所以无需自己再进行各种运算符的重载
	//直接当作int char float类型就ok
	Stack<string> stack;
	cout<<">> 此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？1

	stack.push(string(5,'a'));//匿名对象压栈
	cout<<">> 此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？0

	//将11个字符串压栈
	for(int idx=1;idx!=12;++idx)
	{
		stack.push(string(5,'a'+idx));
	}
	//显示：stack is full,cannot push any more data!
	//      stack is full,cannot push any more data!

	cout<<">>此时栈中是否已满？"<<stack.full()<<endl;
	//显示：>>此时栈中是否已满？1

	while(!stack.empty()){//栈不空时进入循环
		//打印栈顶元素
		cout<<stack.top()<<endl;
		//出栈栈顶元素
		stack.pop();
	}
	//显示：jjjjj
	//      iiiii
	//      hhhhh
	//      ggggg
	//      fffff
	//      eeeee
	//      ddddd
	//      ccccc
	//      bbbbb
	//      aaaaa

	cout<<">>此时栈中是否为空？"<<stack.empty()<<endl;
	//显示：>>此时栈中是否为空？1

	return 0;
}

int main(void)
{
	//test0();
	test1();

	return 0;
}

