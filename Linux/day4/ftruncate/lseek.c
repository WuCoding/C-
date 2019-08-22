#include <func.h>
//文件定位
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	//偏移文件指针
	int ret=lseek(fd,5,SEEK_SET);
	printf("lseek ret=%d\n",ret);

	char buf[128]={0};
	ret=read(fd,&buf,sizeof(buf));
	printf("buf=%s\n",buf);

	return 0;
}

