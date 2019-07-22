#include "head.h"
#include "work_que.h"
#include "factory.h"

int main(int argc,char *argv[])//程序名 IP port pthreadNum capacity userName
{
	if(argc!=6)
	{
		printf("./client ip port threadNum capacity userName\n");
		exit(-1);
	}
	//获得threadNum、capacity、userName
	char userName[20]={0};
	int threadNum,capacity;
	threadNum=atoi(argv[3]);
	capacity=atoi(argv[4]);
	strcpy(userName,argv[5]);
	//定义factory结构体
	Factory_t factoryData;
	//初始化factoryData
	factoryInit(&factoryData,argv[1],argv[2],threadNum,capacity);
	
	
	//创建子线程，使子线程处于等待任务状态
	factoryStart(&factoryData);
	//和服务器进行连接
	int socketFd;
	tcpConnect(&socketFd,argv[1],argv[2]);
	//发送客户端类型 0普通客户端1下载文件子线程2上传文件子线程
	Train_t dataTrain;
	memset(&dataTrain,0,sizeof(Train_t));
	dataTrain.dataLen=sizeof(int);
	int clientType;
	clientType=0;//普通客户端
	memcpy(dataTrain.data,&clientType,dataTrain.dataLen);
	send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
	
	//创建epoll等待队列
	int eplFd;
	eplFd=epoll_create(1);
	struct epoll_event *evs;
	evs=(struct epoll_event*)calloc(2,sizeof(struct epoll_event));
	//监察服务器有无发送信息
	epollAdd(eplFd,socketFd);
	//检查标准输入有无信息可读
	epollAdd(eplFd,STDIN_FILENO);
	int readyFdCount,i;
	char buf[30]={0};
	char commendType[20]={0};
	char fileName[20]={0};
	pNode_t pNewTask;
	int dataLen;
	//存储当前目录id
	char id[20]={0};
	//存储当前路径pwd
	char pwd[200]={0};
	//存储当前目录文件集合
	char catalogue[500]={0};
	while(1)
	{
		readyFdCount=epoll_wait(eplFd,evs,2,-1);
		for(i=0;i<readyFdCount;i++)
		{
			//标准输入可读
			if(evs[i].data.fd==STDIN_FILENO)
			{
				memset(buf,0,sizeof(buf));
				read(STDIN_FILENO,buf,sizeof(buf));
				sscanf(buf,"%s %s",commendType,fileName);
				if(0==strcmp(commendType,"puts")||0==strcmp(commendType,"gets"))//请求类型为上传下载文件
				{
					//将任务放到任务队列里
					pNewTask=(pNode_t)calloc(1,sizeof(Node_t));
					strcpy(pNewTask->commendType,commendType);
					strcpy(pNewTask->fileName,fileName);
					strcpy(pNewTask->id,id);
					pthread_mutex_lock(&factoryData.que.mutex);
					queInsert(&factoryData.que,pNewTask);
					pthread_mutex_unlock(&factoryData.que.mutex);
					pthread_cond_signal(&factoryData.cond);
				}else{  
					//其他短命令
					//发送命令类型
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(commendType);
					memcpy(dataTrain.data,commendType,dataTrain.dataLen);
					send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
					//发送文件名
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(fileName);
					memcpy(dataTrain.data,fileName,dataTrain.dataLen);
					send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
					//发送当前目录id
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(id);
					memcpy(dataTrain.data,id,dataTrain.dataLen);
					send(socketFd,&dataTrain,4+dataTrain.dataLen,0);
				}
			}
			//服务器端有发来消息
			if(evs[i].data.fd==socketFd)
			{
				//接收服务器发来的信息
				//接收当前目录id
				memset(id,0,sizeof(id));
				recvCycle(socketFd,4,&dataLen);
				recvCycle(socketFd,dataLen,id);
				//接收pwd当前路径
				memset(pwd,0,sizeof(pwd));
				recvCycle(socketFd,4,&dataLen);
				recvCycle(socketFd,dataLen,pwd);
				//接收当前目录文件
				memset(catalogue,0,sizeof(catalogue));
				recvCycle(socketFd,4,&dataLen);
				recvCycle(socketFd,dataLen,catalogue);
				system("clear");
				printf("pwd:%s\n",pwd);
				if(0==strlen(catalogue))//目录下为空
				{
					printf("catalogue:\nempty\n");
				}else{
				printf("catalogue:\n%s\n",catalogue);
				}
				printf("commend:");
				fflush(stdout);
			}
		}
	}	
}	
