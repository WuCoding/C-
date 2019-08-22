#include <func.h>

int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int fdw;
	fdw=open(argv[1],O_WRONLY);

	printf("fdw=%d\n",fdw);

	char buf[128]={0};
	read(0,buf,sizeof(buf));

	printf("buf=%s\n",buf);
	write(fdw,buf,strlen(buf));

	return 0;
}
