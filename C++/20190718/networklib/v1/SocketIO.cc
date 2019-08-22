#include "SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//构造函数实现
SocketIO::SocketIO(int fd)
: _fd(fd)
{}

//返回成功读入的字节数，buff为要存入的字符数组，len为要读取的长度
int SocketIO::readn(char *buff,int len)
{
	//left为还未读入的字节数
	int left=len;
	//p为读取数据存入的地址
	char *p=buff;
	while(left>0){//还有未读入的字节则继续循环
		int ret=::read(_fd,p,left);
		//如果read()读到数据为0，那么就表示文件读完了，
		//如果在读的过程中遇到了中断则read()应该返回-1，
		//同时置errno为EINTER。
		if(-1==ret && errno==EINTR){
			//遇到中断
			continue;
		}else if(-1==ret){
			//读入出错
			perror("read");
			//返回读入的字节数
			return len-left;
		}else if(0==ret){
			//对端关闭，read()返回0，
			//返回读入的字节数
			return len-left;
		}else{
			//成功读入了ret个字节
			left-=ret;
			p+=ret;
		}
	}
	//走到这里的都是left=0的
	//返回读入的字节数
	return len-left;
}

//每一次读取一行数据
int SocketIO::readline(char *buff,int maxlen)
{
	//left剩余未读入的字节数
	int left=maxlen-1;
	char *p=buff;
	int ret;
	//存储该行总字节数
	int total=0;
	while(left>0){//还有未读入的字节
		//只是从内核缓冲区拷贝到用户态缓冲区，
		//并未将内核缓冲区中的数据抹除
		ret=recvPeek(p,left);
		//查找'\n'
		for(int idx=0;idx!=ret;++idx){
			if(p[idx]=='\n'){
				//第sz个字节为换行符
				int sz=idx+1;
				//从内核态中的数据拷贝到用户态，
				//同时抹除内核态中的数据。
				//从缓冲区读取sz个字节，将'\n'也读入了，
				//p指针没有发生偏移，说明直接将之前recvPeek获得
				//的数据覆盖掉
				readn(p,sz);				
				total+=sz;
				//将指针偏移
				p+=sz;
				//加上结束符
				*p='\0';
				return total;
			}
		}
		//走到这里，说明没有发现'\n'
		//将内核缓冲区中的数据拷贝到用户态，同时从内核缓冲区中抹除
		//p指针没有偏移，说明也是直接将recvPeek获得的数据覆盖掉
		readn(p,ret);
		left-=ret;
		//p指针偏移
		p+=ret;
		total+=ret;
	}
	//走到这里说明读入了设定的最大字节数，但仍未找到'\n'
	//添加结束符
	*p='\0';
	return total;
}

//从内核缓冲区中的数据拷贝到用户态缓冲区，但不抹除内核缓冲区的数据
int SocketIO::recvPeek(char *buff,int len)
{
	int ret;
	do{
		ret=::recv(_fd,buff,len,MSG_PEEK);
	}while(ret==-1 && errno==EINTR)//遇到中断则继续进行循环，也可能是为了保护该语句
	
	return ret;
}

//向socket描述符写数据，buff为要写入的数据，len为数据的长度
int SocketIO::writen(const char *buff,int len)
{
	//left为未写入的字节数
	int left=len;
	const char *p=buff;
	while(left>0){//还有未写入缓冲区的字节
		int ret=::write(_fd,p,left);
		if(-1==ret && EINTR==errno){
			//遇到中断
			continue;
		}else if(-1==ret){
			//写入出错
			perror("write");
			//返回已写入字节数
			return len-left;
		}else{
			//写入成功
			left-=ret;
			p+=ret;
		}
	}
	//走到这说明left=0
	//返回已成功写入的字节数
	return len-left;
}

}//end of namespace wd






































