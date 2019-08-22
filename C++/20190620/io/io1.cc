#include <iostream>
#include <string>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;

//对标准输入流的每一位（bad,fail,eof,good）的状态进行打印
void printStreamStatus()
{
	cout<<"cin's badbit="<<cin.bad()<<endl
		<<"cin's failbit="<<cin.fail()<<endl
		<<"cin's eofbit="<<cin.eof()<<endl
		<<"cin's goodbit="<<cin.good()<<endl;
}

void test0()
{
	int number;
	printStreamStatus();
	while(cin>>number){ //将标准输入流输入到int型变量number中
		//检查流的状态
		printStreamStatus();
		//输出number的数值
		cout<<">> number ="<<number<<endl;
	}
	printStreamStatus();

	cout<<"clear之后，流的状态："<<endl;
	cin.clear();//重置流的状态，将流的状态位复位
	cin.ignore(1024,'\n');//清空缓冲区，防止重置流的状态后，流将缓冲区剩余的数据重新读入，第一个参数指要清空的最大缓冲区长度，第二个参数指清空到'\n'为止

	//重新打印流的状态
	printStreamStatus();

	string str;
	cin>>str;
	cout<<"str="<<str<<endl;
}

void test1()
{
	cout<<"pls input a interger number:"<<endl;
	int number;
	while(cin>>number,!cin.eof()){//逗号表达式，从左往右进行运算，将右表达式结果作为逗号表达式的结果
		//接收int型数据，到输入流的末尾退出循环
		if(cin.bad()){//如果流发生了不可挽回的异常，直接退出循环
			cout<<">> cin stream status is corrupted!"<<endl;
			return;
		}else if(cin.fail()){//如果流发生输入异常，重置流状态，清空缓冲区
			cout<<"pls input a valid interger number:"<<endl;
			//重置流的状态
			cin.clear();
			//清空缓冲区，第一个参数为最大清空范围，第二个参数表示清空到'\n'为止
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			continue;
		}

		cout<<">> number ="<<number<<endl;
	}
	//查看流的状态
	printStreamStatus();
}
int main(void)
{
	test0();
	test1();
	return 0;
}


			




































