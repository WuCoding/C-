#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	//open失败返回-1 成功返回非负值，但是记住不能写目录文件
	//目录只能写opendir
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}

