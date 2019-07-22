#include<stdio.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"ab+");
	if(NULL==fp)//打开文件失败
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	//文件中内容为helloworld
	fread(buf,sizeof(char),5,fp);//从文件中读5个字节
	printf("buf=%s\n",buf);
	//此时文件偏移指针在w处
	//再次写入查看是否覆盖
	fwrite("how",sizeof(char),3,fp);
	fclose(fp);
	return 0;
}
