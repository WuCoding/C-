#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{
//对socket描述符执行读写操作的类型
class SocketIO
{
	public:
		//构造函数
		explicit
		SocketIO(int fd);

		//读取n个数据
		int readn(char *buff,int len);
		//读取一行数据
		int readline(char *buff,int maxlen);
		//向描述符写数据
		int writen(const char *buff,int len);
	private:
		int recvPeek(char *buff,int len);
	private:
		//数据成员
		int _fd;	//描述符
};

}//end of namespace wd

#endif
