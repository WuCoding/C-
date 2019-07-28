#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

namespace wd
{
//套接字类型
class Socket
{
	public:
		//无参构造函数
		Socket();
		//传fd的构造函数
		Socket(int fd);

		int fd();

		void shutdownWrite();

		//析构函数
		~Socket();
	private:
		//描述符
		int _fd;
};

}//end of namespace wd

#endif
