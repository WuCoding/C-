#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	int value=123;
	int ret;
	ret=write(fd,&value,sizeof(int));
	printf("ret=%d\n",ret);
	return 0;
}
