#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{
//对一个描述符进行IO操作
class SocketIO
{
public:
	//防止隐式转换的构造函数
	explicit
	SocketIO(int fd);

	//读取指定长度的字符
	int readn(char * buff,int len);
	//读取一行数据
	int readline(char * buff,int maxlen);
	//写入数据
	int writen(const char * buff,int len);
private:
	int recvPeek(char * buff,int len);
private:
	//数据成员只有一个描述符
	int _fd;
};

}//end of namespace wd
#endif


