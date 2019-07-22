#include <func.h>
//lseek 将文件指针偏移同时返回指针相对文件开头的位置
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	off_t ret;
	ret=lseek(fd,100,SEEK_SET);
	printf("lseek ret=%ld\n",ret);
	char buf[128]="how";
	write(fd,buf,strlen(buf));
	return 0;
}

