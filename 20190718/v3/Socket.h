#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

namespace wd
{

class Socket
{
	public:
		//构造函数
		Socket();
		explicit
		Socket(int fd);

		int fd() const;

		void shutdownWrite();

		//析构函数
		~Socket();
	private:
		//数据成员
		int _fd;
};
}//end of namespace wd
#endif

