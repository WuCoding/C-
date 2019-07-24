#include "Acceptor.h"
#include "TcpConnection.h"
#include "EventLoop.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//回调函数体现了扩展性
//链接时的回调函数
void onConnection(const wd::TcpConnectionPtr & conn)
{
	cout<<conn->toString()<<" has connected!"<<endl;
	conn->send("welcome to server.");
}

//接受信息时的回调函数
void onMessage(const wd::TcpConnectionPtr & conn)
{
	//该回调函数的执行时间不宜过长 10ms
	string msg=conn->receive();
	cout<<">> receive msg from client:"<<msg<<endl;
	//业务逻辑的处理交给
	//decode
	//compute
	//encode
	conn->send(msg);
}

//关闭套接字时的回调函数
void onClose(const wd::TcpConnectionPtr & conn)
{
	cout<<">>"<<conn->toString()<<"has closed!"<<endl;
}

int main(void)
{
	wd::Acceptor acceptor("192.168.149.128",8888);
	acceptor.ready();

	wd::EventLoop loop(acceptor);
	//注册链接回调函数
	loop.setConnectionCallback(onConnection);
	//注册接收信息时的回调函数
	loop.setMessageCallback(onMessage);
	//注册关闭套接字的回调函数
	loop.setCloseCallback(onClose);

	loop.loop();

	return 0;
}
