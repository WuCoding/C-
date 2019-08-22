#include "SocketIO.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace wd
{

//构造函数，传入一个描述符
SocketIO::SocketIO(int fd)
: _fd(fd)
{}

//从内核缓冲区中读取n个字节
int SocketIO::readn(char *buff,int len)
{
	//剩余还未读入的字节
	int left=len;
	//存储读入的数据的指针
	char *p=buff;
	while(left>0){
		int ret=::read(_fd,p,left);
		if(-1==ret && errno==EINTR){//遇到中断
			continue;
		}else if(-1==ret){//读入出错
			perror("read");
			//返回已读入的字节数
			return len-left;
		}else if(0==ret){//对端关闭
			return len-left;
		}else{//正常读入数据
			left-=ret;
			p+=ret;
		}
	}
	//走到这说明left=0
	return len-left;
}

//每次读取一行数据
int SocketIO::readline(char *buff,int maxlen)
{
	//还剩多少字节未读入
	int left=maxlen-1;
	char *p=buff;
	int ret;
	int total=0;
	while(left>0){
		//复制式读取
		ret=recvPeek(p,left);
		//查找 '\n'
		for(int idx=0;idx!=ret;++idx){
			if(p[idx]=='\n'){
				//找到了'\n'
				int sz=idx+1;//将'\n'也拷贝过去
				readn(p,sz);//剪切式读取
				//总共读入的字节数
				total+=sz;
				//将p指针进行偏移
				p+=sz;
				*p='\0';
				return total;
			}
		}
		//走到这里说明读入的ret个字节中没有'\n'
		readn(p,ret);
		left-=ret;
		p+=ret;
		total+=ret;
	}
	//走到这里说明将maxlen个字节读入，还是没有找到'\n'
	*p='\0';
	//返回总共读入的字节数
	return total;
}

//复制式读取
int SocketIO::recvPeek(char *buff,int len)
{
	int ret;
	do{
		//复制式读取，读取到用户态缓冲区中，
		//但内核缓冲区依然有这个数据，并未
		//被抹掉。
		ret=::recv(_fd,buff,len,MSG_PEEK);
	}while(-1==ret && errno==EINTR);
	return ret;
}

//向描述符中写入数据
int SocketIO::writen(const char *buff,int len)
{
	//剩余未写入内核缓冲区的的字节数
	int left=len;
	//p为要写入内核缓冲区的数据的指针
	const char *p=buff;
	while(left>0){//还有未写入的数据
		int ret=::write(_fd,p,left);
		if(-1==ret && errno==EINTR){//遇到中断
			continue;
		}else if(-1==ret){//读取出错
			perror("write");
			//返回写入成功的字节数
			return len-left;
		}else{//写入正常
			left-=ret;
			p+=ret;
		}
	}
	//走到这里说明left=0
	return len-left;
}
}//end of namespace wd







































