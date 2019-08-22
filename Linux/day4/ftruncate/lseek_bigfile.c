#include <func.h>
//用lseek制造文件空洞，指针偏移后还要写一些数据才会
//有文件空洞
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	int ret=lseek(fd,1000,SEEK_SET);
	printf("ret=%d\n",ret);

	write(fd,"8",1);


	return 0;
}
