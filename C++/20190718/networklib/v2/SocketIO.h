#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{

class SocketIO
{
	public:
		explicit
		SocketIO(int fd);

		//剪切式的读取
		int readn(char *buff,int len);
		int readline(char *buff,int maxlen);
		int writen(const char *buff,int len);

	private:
		//非剪切式的读取
		int recvPeek(char *buff,int len);

	private:
		int _fd;
};
}//end of namespace wd

#endif
