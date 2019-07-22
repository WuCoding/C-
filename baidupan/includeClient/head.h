#ifndef __HEAD_H__
#define __HEAD_H__
#define _GNU_SOURCE
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/select.h>
#include<sys/time.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<errno.h>
#include<signal.h>
#include<strings.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/epoll.h>
#include<sys/uio.h>
#include<mysql/mysql.h>
#define THREAD_ERROR_CHECK(ret,funcName){if(ret!=0){printf("%s:%s\n",funcName,strerror(ret)); return -1;}}
#define ARGS_CHECK(argc,num) {if(num!=argc){printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retVal,funcName) {if(retVal==ret){printf("errno=%d\n",errno);perror(funcName);return -1;}}
typedef struct{
	int dataLen;//数据长度
	char data[1000];//数据内容
}Train_t,*pTrain_t;//传输数据包结构体
int recvCycle(int,int,void*);
int recvFile(int);
int sendFile(int,char*);
int tcpInit(int*,char*,char*);
int tcpConnect(int*,char*,char*);
int epollAdd(int,int);
int epollDel(int,int);
int recvShortCommend(char*,int*,char*,int);
int sendShortCommend(char*,int,char*,int);
#endif
