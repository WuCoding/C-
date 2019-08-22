#include "InetAddress.h"

#include <string.h>

#if 0

struct sockaddr_in
{ 
	//即为sa_family->AF_INET，AF_INET:IPv4网络协议，AF_INET6:IPv6网络协议
	unsigned short int sin_family;
	uint16_t sin_port;		//为使用的port编号
	struct in_addr sin_addr;	//为IP地址
	unsigned char sin_zero[8];	//未使用
};

struct in_addr
{
	uint32_t s_addr; 		//32位网络字节序
};
#endif

namespace wd
{

//只传port的构造函数，ip使用本机地址
InetAddress::InetAddress(unsigned short port)
{
	//清空sockaddr_in结构体对象
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family=AF_INET;
	_addr.sin_port=htons(port);//主机字节序转成网络字节序列
	//inet_addr("0.0.0.0")代表本机地址（一个服务器可能有多个网卡）
	//ip设为本机ip
	_addr.sin_addr.s_addr=INADDR_ANY;
}

//传递ip和port的构造函数
InetAddress::InetAddress(const string &ip,unsigned short port)
{
	//清空sockaddr_in结构体对象
	::memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family=AF_INET;
	//设置port
	_addr.sin_port=htons(port);//主机字节序转成网络字节序列
	//设置ip
	_addr.sin_addr.s_addr=inet_addr(ip.c_str());
}

//传递sockaddr_in结构体对象的构造函数
InetAddress::InetAddress(const struct sockaddr_in &addr)
: _addr(addr)
{}

//获得InetAddress对象的ip值，string类型
string InetAddress::ip() const
{
	//返回一个临时的string类型的对象
	return string(::inet_ntoa(_addr.sin_addr));
}

//获得InetAddress对象的port值
unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);
}

}//end of namespace wd
