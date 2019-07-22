#include <func.h>
//指哪打哪的dup2
//标准输出放到A文件
//标准错误输出放到B文件
int main()
{
	int fd,fdError;
	fd=open("file",O_RDWR);
	ERROR_CHECK(fd,-1,"open");
	fdError=open("file_error",O_RDWR);
	ERROR_CHECK(fdError,-1,"open");
	//首先刷新标准输出
	printf("\n");
	//定义两个描述符
	int fd1,fdError1;
	//执行dup2函数
	fd1=dup2(fd,STDOUT_FILENO);
	//显示fd1的数值
	//下面的两句打印都不会显示在标准输出上了
	//而是写入到了占用标准输入STDOUT_FILENO描述符
	//的文件中
	printf("fd1=%d\n",fd1);
	printf("you can't see me\n");
	return 0;
}
