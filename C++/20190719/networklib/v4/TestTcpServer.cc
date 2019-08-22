#include "Threadpool.h"
#include "TcpServer.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
using std::cout;
using std::endl;
using std::string;

wd::Threadpool *gThreadpool=nullptr;

class Task
{
public:
	//构造函数
	Task(const string &msg,const wd::TcpConnectionPtr &conn)
	: _msg(msg)
	, _conn(conn)
	{}

	//运行在线程池的某一个子线程中
	void process()
	{
		//decode
		//compute
		//encode
		string response=_msg;//要返回给客户端的消息
		//_conn->send(response);  由线程池的线程（计算线程）完成数据的发送，
		//在设计上来说，是不合理的，数据的发送的工作要交还给IO线程（Reactor所在的线程）
		//完成，将send的函数的执行延迟到IO线程取操作
		_conn->sendInLoop(response);
	}
private:
	//数据成员
	string _msg;
	wd::TcpConnectionPtr _conn;
};

//回调函数体现了扩展性
void onConnection(const wd::TcpConnectionPtr & conn)
{
	cout<<conn->toString()<<"has connected!"<<endl;
	conn->send("welcome to server.");
}

void onMessage(const wd::TcpConnectionPtr & conn)
{
	cout<<"onMessage...."<<endl;
	//获得新信息
	string msg=conn->receive();
	cout<<">> receive msg from client:"<<msg<<endl;

	//业务逻辑的处理要交给线程池处理
	//decode
	//compute
	//encode
	//::sleep(2);  碰到需要长时间的处理时，相应速度会降下来
	//conn->send(msg);
	
	Task task(msg,conn);

	//gThreadpool为Threadpool*类型
	gThreadpool->addTask(std::bind(&Task::process,task));
}

void onClose(const wd::TcpConnectionPtr & conn)
{
	cout<<"onClose..."<<endl;
	cout<<conn->toString()<<"has closed!"<<endl;
}

#if 0
using namespace wd;
class EchoServer
{
public:
	void onConnection(const TcpConnectionPtr &conn);
	void onMessage(const TcpConnectionPtr &conn);
	void onClose(const TcpConnectionPtr &conn);

	void process();//业务逻辑的处理

private:
	//数据成员
	Threadpool _threadpool;
	TcpServer _server;
};
#endif

int main(void)
{
	wd::Threadpool threadpool(4,10);//第一个参数为线程数，第二个为任务队列长度
	threadpool.start();//创建子线程

	gThreadpool=&threadpool;
	
	wd::TcpServer server("192.168.30.128",8888);

	//注册回调函数
	server.setConnectionCallback(onConnetion);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);

	//启动
	server.start();

	return 0;
}
