#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	//加了O_EXCL如果文件不存在则创建成功，如果文件存在，
	//则强制创建失败
	fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0666);
	ERROR_CHECK(fd,-1,"open");
	return 0;
}

