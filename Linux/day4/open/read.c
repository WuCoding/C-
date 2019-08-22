#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	char buf[128]={0};
	int cnt=0;
	cnt=read(fd,buf,sizeof(buf));
	printf("buf=%s\n cnt=%d\n",buf,cnt);
	return 0;
}
