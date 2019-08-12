#include "SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//构造函数的实现
SocketIO::SocketIO(int fd)
: _fd(fd)
{}

//读取指定长度的数据，剪切式读取
int SocketIO::readn(char* buff,int len)
{
	//记录还有多少长度未读取
	int left=len;
	//记录存入位置
	char *p=buff;
	while(left>0){//还没到达指定长度的话进入循环
		int ret=::read(_fd,p,left);
		if(-1=ret&&errno==EINTR){//遇到中断，继续循环
			continue;
		}else if(-1==ret){//读取失败，返回已成功读入的字节数
			perror("read");
			return len-left;
		}else if(0==ret){//读取数据长度为0，返回成功读取字节数
			return len-left;
		}else{//读取成功
			//更新剩余字节数
			left-=ret;
			//更新下次读取的位置
			p+=ret;
		}
	}
	//走到这里说明left==0，即指定长度的数据读取完毕
	return len-left;
}

//每次读取一行数据，这里需要用到复制式读取，而不是剪切式读取
int SocketIO::readline(char *buff,int maxlen)
{
	//记录还有多少数据未读入
	int left=maxlen-1;
	//记录存入位置
	char *p=buff;
	int ret;
	//记录总的读取字节数
	int total=0;
	while(left>0){//没到达指定的最大长度，进入循环
		//复制式读取数据
		ret=recvPeek(p,left);
		//从成功读入的ret个字符中查找'\n'
		for(int idx=0;idx!=ret;++idx){
			if(p[idx]=='\n'){//从已成功读入的ret个字符中找到'\n'
				int sz=idx+1;
				//剪切式复制到用户态存储空间，注成功读取ret个字符并未让
				//指针p发生偏移，此时剪切式读取，将覆盖之前读取的数据
				readn(p,sz);
				//更新总的读取长度
				total+=sz;
				//此时才将指针进行偏移
				p+=sz;
				//加上结束符'\0'
				*p='\0';
				//返回总的读入长度
				return total;
			}
		}
		//走到这里说明成功读入的ret个字节的数据中没有找到'\n'，还是将这ret个
		//数据剪切式读取到用户态存储空间
		readn(p,ret);
		//更新剩余的字节数
		left-=ret;
		//更新用户态存储空间的指针
		p+=ret;
		//更新总的读取的字节数
		total+=ret;
	}
	//走到这里说明最大长度读取完毕，也没有找到'\n'，返回成功读取的长度
	return total;	
}

//复制式读取数据
int SocketIO::recvPeek(char *buff,int len)
{
	int ret;
	do{
		//复制式读取，不会清除内核缓冲区的数据
		ret=::recv(_fd,buff,len,MSG_PEEK);
	}while(-1==ret&&errno==EINTR);
	//返回读入的字节数
	return ret;
}

//向描述符中写入数据
int SocketIO::writen(const char *buff,int len)
{
	//记录剩余未写入的字节数
	int left=len;
	//指向要写入的数据
	const char * p=buff;
	while(left>0){
		//记录成功写入的字节数
		int ret::write(_fd,p,left);
		if(-1==ret&&errno==EINTR){//遇到中断
			continue;
		}else if(-1==ret){//写入失败
			perror("write");
			//返回成功写入的字节数
			return len-left;
		}else{//写入ret个字节成功
			//更新剩余字节数
			left-=ret;
			//更新用户态存储区的指针
			p+=ret;
		}
	}
	//走到这里说明要写入的数据已全部写入
	return len-left;
}
}//end of namespace wd
