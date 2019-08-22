#include "TcpServer.h"

namespace wd
{

//构造函数
TcpServer::TcpServer(const string &ip,unsigned short port)
: _acceptor(ip,port)  //将该地址进行监听
, _loop(_acceptor)  //将监听连接的描述符加入epoll，同时将链接产生的描述符也加入到epoll中
{}

void TcpServer::start()
{
	//将该地址进行绑定和监听
	_acceptor.ready();
	//开始查看准备就绪的描述符
	_loop.loop();
}

//设置链接时的回调函数
void TcpServer::setConnectionCallback(TcpConnectionCallback &&cb)
{
	_loop.setConnectionCallback(std::move(cb));
}

//设置接受信息时的回调函数
void TcpServer::setMessageCallback(TcpConnectionCallback &&cb)
{
	_loop.setMessageCallback(std::move(cb));
}

//设置关闭套接字时的回调函数
void TcpServer::setCloseCallback(TcpConnectionCallback &&cb)
{
	_loop.setCloseCallback(std::move(cb));
}

}//end of namespace wd



