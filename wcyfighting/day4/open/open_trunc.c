#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	//将原本存在的文件截断为0
	fd=open(argv[1],O_RDWR|O_TRUNC);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}

