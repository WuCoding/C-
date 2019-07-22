#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	//如果文件存在那么再次创建同名文件强制失败 O_EXCL	
	fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}

