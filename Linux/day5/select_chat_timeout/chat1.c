#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdr=open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");
	fdw=open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");

	printf("I am chat1,fdr=%d,fdw=%d\n",fdr,fdw);

	char buf[128]={0};
	//描述符数组
	fd_set rdset;
	//已就绪描述符的数量
	int fdReadyNum;
	int ret;
	struct timeval tv;
#if 0
	struct timeval
	{
		time_t tv_sec;  	//秒
		suseconds_t tv_usec; 	//微秒
	};
#endif
	while(1)
	{
		//清空描述符数组
		FD_ZERO(&rdset);
		//加入监控的描述符
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);

		//设置超时时间
		tv.tv_sec=3;
		tv.tv_usec=0;

		fdReadyNum=select(fdr+1,&rdset,NULL,NULL,&tv);
		if(fdReadyNum>0){//有监控的描述符就绪导致唤醒，而不是超时导致
			if(FD_ISSET(STDIN_FILENO,&rdset)){//标准输入可读
				memset(buf,0,sizeof(buf));
				//读取标准输入
				ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
				if(0==ret){
					printf("close\n");
					break;
				}
				//写入管道中
				write(fdw,buf,strlen(buf)-1);//这里-1是去掉'\n'
			}

			if(FD_ISSET(fdr,&rdset)){//管道可读
				memset(buf,0,sizeof(buf));
				//从管道中读取数据
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret){//对端关闭导致管道可读
					printf("byebye\n");
					break;
				}
				//打印从管道中读取的数据
				printf("buf=%s\n",buf);
			}
		}else{//超时还没有描述符就绪
			printf("timeout,do other thing\n");
		}

	}

	return 0;
}

