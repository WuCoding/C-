#include <stdio.h>

int main(int argc,char *argv[])
{
	if(argc!=2){
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"rb+");
	if(NULL==fp){
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fread(buf,sizeof(char),5,fp);

	long pos;
	pos=ftell(fp);

	printf("buf=%s,pos=%ld\n",buf,pos);
	fwrite("how",sizeof(char),3,fp);
	fclose(fp);
	return 0;
}
