#include <iostream>
using std::cout;
using std::endl;

template <class...Args> //Args 模板参数包
void print(Args...args) //args 函数参数包
{
	cout<<sizeof...(Args)<<endl;//打印类型个数
	cout<<sizeof...(args)<<endl;//打印参数个数
}

//函数模板重载
template<class T>
void display(T t)
{
	cout<<"--------------display(T t)-----------------"<<endl;
	cout<<t<<endl;
}

template<class T,class...Args>
void display(T t,Args...args)
{
	cout<<"---------display(T t,Args...args)-----------"<<endl;
	cout<<t<<endl;
	display(args...);//函数参数包的展开（拆包）
}

int main(void)
{
	display(10,11.11,'a',"hello");
	//显示：------------------display(T t,Args...args)---------------------
	//      10
	//      ------------------display(T t,Args...args)---------------------
	//      11.11
	//      ------------------display(T t,Args...args)---------------------
	//      a
	//      ------------------------display(T t)---------------------------
	//      hello
	
	//执行过程：
	//display(10,11.11,'a',"hello");调用display(T t,Args...args)
	//|---->cout<<10<<endl;
	//|---->display(11.11,'a',"hello");调用display(T t,Args...args)
	//      |---->cout<<11.11<<endl;
	//      |---->display('a',"hello");调用display(T t,Args...args)
	//            |---->cout<<'a'<<endl;
	//            |---->display("hello"); 调用display(T t)
	//                  |---->cout<<"hello"<<endl;

	return 0;
}
