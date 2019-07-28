#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
	wd::Acceptor acceptor("192.168.149.128",8888);
	acceptor.ready();
	//ready()函数进行的操作：
	//将地址设为重用
	//将端口设为重用
	//将套接口绑定ip和port----bind()
	//将套接口进入监听模式----listen()
	wd::TcpConnection conn(acceptor.accept());
	//accept()函数进行的操作：
	//接受链接的请求，返回连接后的套接字
	cout<<conn.toString()<<"has connected!"<<endl;
	conn.send("welcome to server.");
	printf(">pls client data:\n");
	cout<<conn.receive()<<endl;

	return 0;
}

