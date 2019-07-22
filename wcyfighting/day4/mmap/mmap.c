#include <func.h>
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fd;
	fd=open(argv[1],O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	printf("fd=%d\n",fd);
	//mmap第一个参数表示要映射的堆内存地址空间（填NULL则系统自动分配一个堆内存地址空间），第二个参数为要映射的文件大小(要写4k的整数倍，即使没有写4k的整数倍，也是用物理页的整倍数)，第三个参数为对文件的操作权限，第五个为要映射的文件的描述符，第六个参数为文件偏移量（从文件的那个位置开始映射）该值必须是4k的整数倍
	char *p;
	//注意mmap不能改变文件大小,而且p不能偏移，不然munmap时就会造成崩溃
	p=(char*)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ERROR_CHECK(p,(char*)-1,"mmap");
	p[0]='H';
	//第一个参数为mmap得到的指针，第二个参数为映射的文件大小，此值必须与mmap填的参数一致
	int ret;
	//成功返回0 失败返回-1
	ret=munmap(p,5);//munmap回去就是写回磁盘
	ERROR_CHECK(ret,-1,"munmap");
	return 0;
}

