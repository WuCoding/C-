#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,3);

	int fdr=open(argv[1],O_RDONLY);
	ERROR_CHECK(fdr,-1,"open");

	int fdw=open(argv[2],O_WRONLY);
	ERROR_CHECK(fdw,-1,"open");

#if 0
typedef long int __fd_mask;
typedef struct
{
	__fd_mask __fds_bits[1024/(8*(int)sizeof(__fd_mask))];
}fd_set;
#endif
	char buf[128]={0};
	fd_set rdset;//描述符数组
	int fdReadyNum;//就绪的描述符的数量
	int ret;

	while(1)
	{
		//将描述符数组清空
		FD_ZERO(&rdset);
		//将标准输入加入到监控数组中
		FD_SET(STDIN_FILENO,&rdset);
		//将管道读端的描述符加入到监控数组中
		FD_SET(fdr,&rdset);
		//第1参数:监控描述符的最大值+1
		//第2参数:传入传出参数
		fdReadyNum=select(fdr+1,&rdset,NULL,NULL,NULL);
		
		//-------判断哪些描述符已就绪-----------
		if(FD_ISSET(STDIN_FILENO,&rdset)){
			//判断标准输入是否可读
			memset(buf,0,sizeof(buf));
			read(STDIN_FILENO,buf,sizeof(buf)-1);
			write(fdw,buf,strlen(buf)-1);
		}

		if(FD_ISSET(fdr,&rdset)){
			//判断管道读端是否可读
			memset(buf,0,sizeof(buf));
			ret=read(fdr,buf,sizeof(buf)-1);
			if(0==ret){//对端关闭，退出聊天
				printf("对端关闭\n");
				break;
			}
			printf("buf=%s\n",buf);
		}
	}

	return 0;
}




