#include <func.h>
//ftruncate 改变文件大小,改大往文件后面填0，改小则截断文件内容
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	//将描述符fd表示的文件改大成100个字节
	int ret;
	ret=ftruncate(fd,3);
	ERROR_CHECK(ret,-1,"ftruncate");
	return 0;
}

