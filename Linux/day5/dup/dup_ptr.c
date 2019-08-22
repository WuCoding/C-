#include <func.h>
//dup后内核里只有一个文件对象，只有一个ptr指针

int main()
{
	int fd,fd1;
	fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");

	fd1=dup(fd);
	printf("fd1=%d\n",fd1);
	char buf[128]={0};
	int ret;
	//将通过fd描述符来将文件的指针偏移
	lseek(fd,5,SEEK_SET);
	//通过fd1描述符来读取文件的内容
	ret=read(fd1,buf,sizeof(buf)-1);
	ERROR_CHECK(ret,-1,"read");
	printf("buf=%s\n",buf);
	//会发现其实fd和fd1的文件偏移指针共用一个
	return 0;
}
