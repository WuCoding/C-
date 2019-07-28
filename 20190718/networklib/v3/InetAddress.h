#ifndef __WD_INETADDRESS_H__
#define __WD_INETADDRESS_H__

#include <arpa/inet.h>
#include <string>
using std::string;

namespace wd
{
//某端的地址，ip和port
class InetAddress
{
	public:
		//构造函数
		//传端口的构造函数
		explicit
		InetAddress(unsigned short port);
		//传ip和端口port的构造函数
		InetAddress(const string &ip,unsigned short port);
		//传sockaddr_in结构体的构造函数
		InetAddress(const struct sockaddr_in &addr);

		string ip() const;
		unsigned short port() const;
		struct sockaddr_in * getInetAddressPtr()
		{
			return &_addr;
		}

	private:
		//数据成员
		struct sockaddr_in _addr;
};

}//end of namespace wd
#endif

