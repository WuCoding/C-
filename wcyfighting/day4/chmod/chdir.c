#include <func.h>

//改变当前路径chdir
int main()
{
	char buf[1024]={0};
	char *pRet;
	//getcwd函数成功返回buf的首地址 失败返回 NULL
	pRet=getcwd(buf,sizeof(buf));
	ERROR_CHECK(pRet,NULL,"getcwd");
	printf("buf=%s\n",buf);
	//如果怕路径比buf长导致访问越界也可以像下面这样用，让系统自动分配一个长度合适的字符数组
	chdir("/tmp");
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
