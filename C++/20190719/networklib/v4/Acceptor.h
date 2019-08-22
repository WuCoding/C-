#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "InetAddress.h"
#include "Socket.h"

namespace wd
{

class Acceptor
{
public:
	//构造函数，传递port
	Acceptor(unsigned short port);
	//构造函数，传递ip和port
	Acceptor(const string &ip,unsigned short port);

	void ready();

	int accept();
	int fd() const
	{
		return _listensock.fd();
	}

private:
	//设置地址重用
	void setReuseAddr(bool on);
	//设置端口号重用
	void setReusePort(bool on);

	//将监听描述符与ip和port绑定
	void bind();
	//将监听链接描述符处于监听状态
	void listen();

private:
	//数据成员
	InetAddress _addr;//地址
	Socket _listensock;//监听链接描述符
};

}//end of namespace wd

#endif
