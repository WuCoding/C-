#include "TcpServer.h"

namespace wd
{

//构造函数
TcpServer::TcpServer(const string &ip,unsigned short port)
: _acceptor(ip,port)
, _loop(_acceptor)
{}

//启动函数
void TcpServer::start()
{
	_acceptor.ready();//使套接字进入监听模式
	_loop.loop();//开始轮询已就绪的描述符
}

//注册链接时的回调函数
void TcpServer::setConnectionCallback(TcpConnectionCallback &&cb)
{
	_loop.setConnectionCallback(std::move(cb));
}

//注册有新信息时的回调函数
void TcpServer::setMessageCallback(TcpConnectionCallback &&cb)
{
	_loop.setMessageCallback(std::move(cb));
}

//注册关闭链接时的回调函数
void TcpServer::setCloseCallback(TcpConnectionCallback &&cb)
{
	_loop.setCloseCallback(std::move(cb));
}

}//end of namespace wd
