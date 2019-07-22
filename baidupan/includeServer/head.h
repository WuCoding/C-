#ifndef __HEAD_H__
#define __HEAD_H__
#define _GNU_SOURCE
#include<sys/stat.h>
#include<stdio.h>
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
#include<string.h>
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
int recvCycle(int,int,void*);//循环接受
int recvFile(int);//发送文件
int sendFile(int,char*);//接收文件
int tcpInit(int*,char*,char*);//服务器用来监听
int tcpConnect(int*,char*,char*);//客户端用来链接
int epollAdd(int,int);//将描述符加到epoll红黑树上
int epollDel(int,int);//将描述符从epoll红黑树上删除

//实现短命令函数--------------------------------------------------------------------------------------
int cdRoot(char*);//获得根目录下的文件表
int cdSelfID(char*,char*);//显示id下的文件信息
int cdCommend(char*,char*,char*);//实现cd命令
int cdFormer(char*,char*);//实现cd..命令
int makeDirent(char*,char*,char*,char*);//实现mkdir命令
int cataloguePwd(char*,char*);//实现pwd功能
//实现remove功能的数据结构-------------------------------------------------------------
typedef struct id_node{
	char id[20];//用来存储要删除的数据库中的一行id
	struct id_node *pNext;
}IDnode_t,*pIDnode_t;//删除队列的节点
typedef struct{
	pIDnode_t queHead,queTail;//删除队列头和队列尾
	int size;//队列中节点数
}QueID_t,*pQueID_t;//队列结构
//实现remove功能的函数-----------------------------------------------------------------
int getID(pQueID_t,char*);//从队列头部拿出id信息，队列为空返回-1
int insertID(pQueID_t,char*);//将新节点插入队列尾
int getRootID(char*,char*);//输入父目录id和文件名/获得目标id
int smallDelete(char*);//将输入的id的一行信息删除
int getChildID(pQueID_t,char*);//获得id的孩子id，并将孩子id依次加入到队列中
int removeCatalogue(char*,char*);//删除目录所有操作

#endif
