#include <func.h>
//描述符的赋值与复制
int main()
{
	int fd,fd1;
	fd=open("file",O_RDWR);
	printf("fd=%d\n",fd);
	ERROR_CHECK(fd,-1,"open");
	//进行描述符的赋值
	//fd1=fd;
	//进行描述符的复制,这两个描述符指向同一个文件对象，所以不能并行的写文件，文件偏移指针只有一个，可以mmap到内存里面，并行操作内存段，是可以实现并行写文件的
	fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	close(fd);
	char buf[128]={0};
	int ret;
	ret=read(fd1,buf,sizeof(buf));
	ERROR_CHECK(ret,-1,"read");
	printf("buf=%s\n",buf);
	return 0;
}
