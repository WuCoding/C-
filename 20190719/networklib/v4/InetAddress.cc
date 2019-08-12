#include "InetAddress.h"

#include <string.h>

namespace wd
{

//传port构造函数，ip为本端ip
InetAddress::InetAddress(unsigned short port)
{
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);
	_addr.sin_addr.s_addr=INADDR_ANY;
}

//传ip和port构造函数
InetAddress::InetAddress(const string &ip,unsigned short port)
{
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);
	_addr.sin_addr.s_addr=inet_addr(ip.c_str());
}

//传sockaddr_in结构体的构造函数
InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr)
{}

//获得该对象的ip
string InetAddress::ip() const
{
	return string(::inet_ntoa(_addr.sin_addr));
}

//获得该对象的port
unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);
}
}//end of namespace wd
