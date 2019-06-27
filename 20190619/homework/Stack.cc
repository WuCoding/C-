#include <iostream>
using std::cout;
using std::endl;

class Stack
{
	public:
		//构造函数
		Stack()
		: _pos(0)
		{
			cout<<"栈创建成功！"<<endl;
		}
		//元素入栈
		void push(int num)
		{
			if(_pos==10)
			{
				cout<<"栈已满入栈失败"<<endl;
			}else{
			_stack[_pos]=num;
			_pos++;
			}
		}
		//元素出栈
		void pop()
		{
			if(_pos==0)
			{
				cout<<"栈为空，出栈失败"<<endl;
			}else{
			_pos--;
			}
		}
		//读出栈顶元素
		int top()
		{
			if(_pos==0)
			{
				cout<<"栈为空，读取元素失败"<<endl;
				return -1;
			}else{

			return _stack[_pos-1];
			}
		}
		//判断栈空
		bool empty()
		{
			if(_pos==0)//栈为空
			{
				return 1;
			}else{//栈不空
				return 0;
			}
		}
		//判断栈为满
		bool full()
		{
			if(_pos==10)//栈已满
			{
				return 1;
			}else{
				return 0;
			}
		}
	private:
		int _stack[10];
		int _pos;
};

int main(void)
{
	Stack p;
	p.push(10);
	p.push(12);
	p.push(14);
	cout<<"p.top()="<<p.top()<<endl;
	p.pop();
	cout<<"p.top()="<<p.top()<<endl;
	return 0;
}

