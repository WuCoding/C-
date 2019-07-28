#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "InetAddress.h"
#include "Socket.h"

namespace wd
{
//将套接字和地址绑定起来，并让套接字进行链接监听
class Acceptor
{
	public:
		//传port构造函数，ip为本机ip
		Acceptor(unsigned short port);
		Acceptor(const string &ip,unsigned short port);
		void ready();

		int accept();
		//获得监听链接的描述符
		int fd() const
		{
			return _listensock.fd();
		}
	private:
		void setReuseAddr(bool on);
		void setReusePort(bool on);
		void bind();
		void listen();

	private:
		//数据成员
		InetAddress _addr;
		Socket _listensock;
};
}//end of namespace wd
#endif

