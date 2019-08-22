#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "InetAddress.h"
#include "Socket.h"

namespace wd
{

//该类的作用将描述符和地址绑定起来，并将描述符进行监听和进行链接
class Acceptor
{
	public:
		//传port端口号构造函数
		Acceptor(unsigned short port);
		//传ip地址和port端口号构造函数
		Acceptor(const string &ip,unsigned short port);
		//准备函数
		void ready();

		//处于监听状态的服务器，监听描述符有数据时，进行accept()和客户端进行链接
		//该函数返回的是进行交流的新的socket描述符
		int accept();
	private:
		//设置地址重用
		void setReuseAddr(bool on);
		//设置端口号重用
		void setReusePort(bool on);
		//使套接口与指定的port和ip地址关联
		void bind();
		//使服务器的这个端口和ip处于监听状态
		void listen();
	private:
		//数据成员
		InetAddress _addr;	//地址类型对象
		Socket _listensock;	//监听描述符
};

}//end of namespace wd

#endif

