#ifndef __WD_INETADDRESS_H__
#define __WD_INETADDRESS_H__

#include <arpa/inet.h>
#include <string>
using std::string;

namespace wd
{

class InetAddress
{
	public:
		//构造函数
		explicit
		InetAddress(unsigned short port);
		InetAddress(const string &ip,unsigned short port);
		InetAddress(const struct sockaddr_in &addr);

		//获得ip
		string ip() const;
		//获得port
		unsigned short port() const;
		//获得sockaddr_in结构体指针
		struct sockaddr_in * getInetAddressPtr()
		{
			return &_addr;
		}

	private:
		//数据成员
		struct sockaddr_in _addr; //存储一个进程的sockaddr_in结构体
};

}//end of namespace wd

#if 0
struct sockaddr_in
{
	unsigned short int sin_family; 		//即为sa_family->AF_INET
	uint16_t sin_port;  			//为使用的port编号
	struct in_addr sin_addr;		//为IP地址
	unsigned char sin_zero[8]; 		//未使用
};

struct in_addr
{
	uint32_t s_addr;			//32位网络字节序
};
#endif

#endif
