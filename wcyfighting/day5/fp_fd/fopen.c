#include <func.h>
//文件描述符和文件指针的转换
int main()
{
	FILE *fp=fopen("file","rb+");
	int fd;
	//将文件指针转换为文件描述符
	fd=fileno(fp);
	write(fd,"hello",5);
	fclose(fp);
	return 0;
} 
