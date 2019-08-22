#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{
//传入一个描述符来对该描述符进行读写操作，因为套接字是全双工的
class SocketIO
{
	public:
		//构造函数
		explicit
		SocketIO(int fd);

		//从描述符中读取n个字节
		int readn(char *buff,int len);//剪切式读取
		//从描述符中读取一行，即读到\n为止
		int readline(char *buff,int maxlen);
		//向描述符中写入n个字节
		int writen(const char *buff,int len);
	private:
		int recvPeek(char *buff,int len);//复制式读取
	private:
		//数据成员
		int _fd;//进行读写操作的描述符
};
}//end of namespace wd
#endif


