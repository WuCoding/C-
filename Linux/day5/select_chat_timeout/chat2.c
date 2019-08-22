#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);
	int fdr,fdw;
	fdw=open(argv[1],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");
	fdr=open(argv[2],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");

	printf("I am chat2 fdw=%d,fdr=%d\n",fdw,fdr);
	char buf[128]={0};
	//描述符数组
	fd_set rdset;
	//就绪描述符数量
	int fdReadyNum;
	int ret;
	struct timeval tv;
	while(1)
	{
		//将数组清空
		FD_ZERO(&rdset);
		//将要监控的描述符加入到数组中
		FD_SET(STDIN_FILENO,&rdset);
		FD_SET(fdr,&rdset);

		//设置超时时间
		tv.tv_sec=3;
		tv.tv_usec=0;

		fdReadyNum=select(fdr+1,&rdset,NULL,NULL,&tv);
		if(fdReadyNum>0){//有描述符就绪
			if(FD_ISSET(STDIN_FILENO,&rdset)){//标准输入可读
				memset(buf,0,sizeof(buf));
				ret=read(STDIN_FILENO,buf,sizeof(buf)-1);
				if(0==ret){
					printf("close\n");
					break;
				}
				//将标准输入的数据写入管道中
				write(fdw,buf,strlen(buf)-1);
			}

			if(FD_ISSET(fdr,&rdset)){//管道有数据可读
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret){//对端关闭导致描述符可读
					printf("byebye\n");
					break;
				}

				//将管道中的数据打印出来
				printf("buf=%s\n",buf);
			}
		}else{//超时
			printf("time out!\n");
		}
	}

	return 0;
}



