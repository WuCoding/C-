#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	//open失败返回-1 成功返回非负值，但是记住不能写目录文件
	//目录只能写opendir
	int fd;
	//如果没有该文件则进行创建,如果有该文件则不进行创建只是把文件打开,创建时要加上文件权限，该文件权限也受掩码影响
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	return 0;
}

