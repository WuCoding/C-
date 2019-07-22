#include "head.h"
#include "work_que.h"
#include "factory.h"

int main(int argc,char *argv[])//程序名 ip port threadNum capacity
{
	if(argc!=5)
	{
		printf("./server ip port threadNum capacity\n");
		exit(-1);
	}
	//获得threadNum、capacity
	int threadNum,capacity;
	threadNum=atoi(argv[3]);
	capacity=atoi(argv[4]);
	//定义factory结构体
	Factory_t factoryData;
	//初始化factoryData
	factoryInit(&factoryData,threadNum,capacity);
	//创建子线程,使子线程处于等待任务状态
	factoryStart(&factoryData);
	//使主线程处于监听状态
	int socketFd;
	tcpInit(&socketFd,argv[1],argv[2]);
	//创建epoll等待队列
	int eplFd;
	eplFd=epoll_create(1);
	struct epoll_event *evs;
	evs=(struct epoll_event*)calloc(15,sizeof(struct epoll_event));
	epollAdd(eplFd,socketFd);//监察有无客户端链接
	int readyFdCount;
	int newFd,clientType,dataLen;
	int fdMonitorCount=1,i;
	pNode_t pNewTask;
	char id[20]={0};
	char commendType[20]={0};
	char fileName[20]={0};
	char pwd[200]={0};
	char catalogue[1000]={0};
	Train_t dataTrain;
	while(1)
	{
		readyFdCount=epoll_wait(eplFd,evs,fdMonitorCount,-1);
		for(i=0;i<readyFdCount;i++)
		{
			//有新的客户端链接
			if(evs[i].data.fd==socketFd)
			{
				newFd=accept(socketFd,NULL,NULL);
				//接收客户端类型
				recv(newFd,&dataLen,4,0);
				recv(newFd,&clientType,dataLen,0);
				printf("newFd %d clientType %d\n",newFd,clientType);
				if(0==clientType)//普通客户端
				{
					//将描述符加入到epoll中
					epollAdd(eplFd,newFd);
					fdMonitorCount++;
					//发送目录id=0
					memset(id,0,sizeof(id));
					strcpy(id,"0");
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(id);
					memcpy(dataTrain.data,id,dataTrain.dataLen);
					send(newFd,&dataTrain,4+dataTrain.dataLen,0);
					
					//发送当前路径
					memset(pwd,0,sizeof(pwd));
					strcpy(pwd,"/");
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(pwd);
					memcpy(dataTrain.data,pwd,dataTrain.dataLen);
					send(newFd,&dataTrain,4+dataTrain.dataLen,0);
					//发送当前目录文件
					memset(catalogue,0,sizeof(catalogue));
					cdRoot(catalogue);
					memset(&dataTrain,0,sizeof(Train_t));
					dataTrain.dataLen=strlen(catalogue);
					memcpy(dataTrain.data,catalogue,dataTrain.dataLen);
					send(newFd,&dataTrain,4+dataTrain.dataLen,0);
				}else{//1下载文件子线程2上传文件子线程
					//将任务节点放到任务队列
					pNewTask=(pNode_t)calloc(1,sizeof(Node_t));
					//将下载上传文件描述符发给子线程
					pNewTask->newFd=newFd;
					//将任务类型发送给子线程
					pNewTask->flag=clientType;
					//将上传下载任务放到任务队列中
					pthread_mutex_lock(&factoryData.que.mutex);
					queInsert(&factoryData.que,pNewTask);
					pthread_mutex_unlock(&factoryData.que.mutex);
					pthread_cond_signal(&factoryData.cond);
	
				}
				continue;
			}
			//客户端描述符有消息可读,描述符为evs[i].data.fd
			//接收命令类型
			memset(commendType,0,sizeof(commendType));
			recvCycle(evs[i].data.fd,4,&dataLen);
			recvCycle(evs[i].data.fd,dataLen,commendType);
			printf("commendType=%s\n",commendType);
			//接收文件名
			memset(fileName,0,sizeof(fileName));
			recvCycle(evs[i].data.fd,4,&dataLen);
			recvCycle(evs[i].data.fd,dataLen,fileName);
			printf("fileName=%s\n",fileName);
			//接收id
			memset(id,0,sizeof(id));
			recvCycle(evs[i].data.fd,4,&dataLen);
			recvCycle(evs[i].data.fd,dataLen,id);
			printf("id=%s\n",id);
			
			if((0==strcmp(commendType,"cd"))&&(0==strcmp(fileName,"..")))
			{
				//命令是cd ..-------------------------------------------
				memset(catalogue,0,sizeof(catalogue));				
				cdFormer(id,catalogue);
				memset(pwd,0,sizeof(pwd));
				if(0==strcmp(id,"0"))//此时要显示根目录的当前路径
				{
					strcpy(pwd,"/");
				}else{
					cataloguePwd(id,pwd);
				}
				
				//发送id
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(id);
				memcpy(dataTrain.data,id,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前路径
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(pwd);
				memcpy(dataTrain.data,pwd,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前目录文件
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(catalogue);
				memcpy(dataTrain.data,catalogue,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
			}else if(0==strcmp(commendType,"cd")){
				//命令是cd fileName----------------------------------------
				memset(catalogue,0,sizeof(catalogue));
				cdCommend(id,fileName,catalogue);
				memset(pwd,0,sizeof(pwd));
				cataloguePwd(id,pwd);
				//发送id
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(id);
				memcpy(dataTrain.data,id,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前路径
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(pwd);
				memcpy(dataTrain.data,pwd,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前目录文件
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(catalogue);
				memcpy(dataTrain.data,catalogue,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
			}else if(0==strcmp(commendType,"remove")){
				//命令是remove fileName---------------------------------------
				removeCatalogue(id,fileName);
				memset(catalogue,0,sizeof(catalogue));
				cdSelfID(id,catalogue);
				memset(pwd,0,sizeof(pwd));
				if(0==strcmp(id,"0"))//此时目录为根目录
				{
					strcpy(pwd,"/");
				}else{
					cataloguePwd(id,pwd);
				}
				//发送id
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(id);
				memcpy(dataTrain.data,id,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前路径
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(pwd);
				memcpy(dataTrain.data,pwd,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前目录文件
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(catalogue);
				memcpy(dataTrain.data,catalogue,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
			}else if(0==strcmp(commendType,"mkdir")){
				//命令是mkdir fileName
				makeDirent("wcy",id,fileName,"c");
				printf("makeDirent语句执行成功\n");
				memset(catalogue,0,sizeof(catalogue));
				cdSelfID(id,catalogue);
				memset(pwd,0,sizeof(pwd));
				if(0==strcmp(id,"0"))//此时目录为根目录
				{
					strcpy(pwd,"/");
				}else{
					cataloguePwd(id,pwd);
				}
				//发送id
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(id);
				memcpy(dataTrain.data,id,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前路径
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(pwd);
				memcpy(dataTrain.data,pwd,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
				//发送当前目录文件
				memset(&dataTrain,0,sizeof(Train_t));
				dataTrain.dataLen=strlen(catalogue);
				memcpy(dataTrain.data,catalogue,dataTrain.dataLen);
				send(evs[i].data.fd,&dataTrain,4+dataTrain.dataLen,0);
			}
		}	
	}
}

