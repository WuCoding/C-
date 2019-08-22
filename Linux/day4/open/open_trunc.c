#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	//O_TRUNC该标志将文件截断为0
	fd=open(argv[1],O_RDWR|O_TRUNC);
	return 0;
}
