#include <func.h>

int main()
{
	int fd,fd1;
	fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");

	fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	close(fd);
	char buf[128]={0};

	int ret=read(fd1,buf,sizeof(buf));

	ERROR_CHECK(ret,-1,"read");

	printf("buf:%s\n",buf);

	return 0;
}
