#include <func.h>
int main()
{
	int fd,fd1;
	fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	//首先刷新标准输出
	printf("\n");
	//关闭标准输出
	close(STDOUT_FILENO);
	fd1=dup(fd);
	//显示fd1的数值
	//下面的两句打印都不会显示在标准输出上了
	//而是写入到了占用标准输入STDOUT_FILENO描述符
	//的文件中
	printf("fd1=%d\n",fd1);
	printf("you can't see me\n");
	return 0;
}
