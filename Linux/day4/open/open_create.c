#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	//如果要创建的话就要写权限，如果文件已经创建，
	//则不会再次创建，而只是把它打开
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}
	

