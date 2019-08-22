#include <func.h>

int main()
{
	char buf[1024]={0};
	char *pRet;
	pRet=getcwd(buf,sizeof(buf));
	ERROR_CHECK(pRet,NULL,"getcwd");
	printf("buf=%s\n",buf);

	//改变目录
	chdir("/tmp");
	printf("path=%s\n",getcwd(NULL,0));
	return 0;
}
