#include <iostream>
using std::cout;
using std::endl;
//循环数组实现队列操作,头尾相等队列为空，尾+1=头表示队列满，
class Queue
{
	public:
		//构造函数
		Queue()
		: _posHead(0)
		, _posTail(0)
		{
			cout<<"队列创建完毕"<<endl;
		}
		//元素入队——尾插
		void push(int num)
		{
			if((_posTail+1)%20==_posHead)//队列满
			{
				cout<<"队列已满，入队失败"<<endl;
			}else{
				_queue[_posTail]=num;
				_posTail=(_posTail+1)%20;
			}
		}
		//元素出队——头出
		void pop()
		{
			if(_posTail==_posHead)//队列为空
			{
				cout<<"队列为空，出队失败"<<endl;
			}else{
				_posHead=(_posHead+1)%20;
			}
		}
		//读取队头元素
		int front()
		{
			if(_posHead==_posTail)//队列为空
			{
				cout<<"队列为空，读取失败"<<endl;
				return -1;
			}else{
				return _queue[_posHead];
			}
		}
		//读取队尾元素
		int back()
		{
			if(_posHead==_posTail)//队列为空
			{
				cout<<"队列为空，读取失败"<<endl;
				return -1;
			}else{
				return _queue[(_posTail+19)%20];
			}
		}
		//判断队列是否为空
		bool empty()
		{
			if(_posTail==_posHead)//队列为空
			{
				return 1;
			}else{
				return 0;
			}
		}
	private:
		int _queue[20];
		int _posHead;
		int _posTail;
};

int main(void)
{
	Queue que;
	que.push(20);
	que.push(30);
	que.push(40);
	que.push(50);
	cout<<que.front()<<endl;
	que.pop
