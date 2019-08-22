#include <func.h>

//因为ftruncate改变文件的大小，所以它是需要文件的写权限的

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	//将该文件改为100字节大小
	int ret=ftruncate(fd,3);
	ERROR_CHECK(ret,-1,"ftruncate");
	return 0;
}

