#include <func.h>

int main()
{
	int fd,fd1;
	fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");

	printf("\n");
	close(STDOUT_FILENO);
	fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	
	printf("you can't see me\n");
	return 0;
}
	
