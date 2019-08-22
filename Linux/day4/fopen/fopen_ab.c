#include <stdio.h>
//ab+只要一执行写操作就先将光标偏移到文件尾，再进行写操作
int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("error args\n");
		return -1;
	}
	//文件指针
	FILE *fp;
	fp=fopen(argv[1],"ab+");
	if(NULL==fp){
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fread(buf,sizeof(char),5,fp);
	printf("buf=%s\n",buf);
	fwrite("how",sizeof(char),3,fp);
	fclose(fp);
	return 0;
}
