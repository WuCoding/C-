#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);

	char *p;
	//第一个参数为从内存中找的空间的起始地址，
	//最后一个参数为从文件的哪个位置开始映射
	p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ERROR_CHECK(p,(char*)-1,"mmap");
	p[0]='H';
	//注意p指针不能偏移，否则在munmap时就会崩溃
	//第二个参数为映射空间的大小
	int ret=munmap(p,5);//munmap实际就是将内存中的数据写回磁盘
	ERROR_CHECK(ret,-1,"munmap");

	return 0;
}
