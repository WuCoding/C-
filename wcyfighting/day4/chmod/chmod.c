#include<func.h>

//改变文件权限chmod
int main(int argc,char* argv[])
{

	ARGS_CHECK(argc,2);
	int ret;
	ret=chmod(argv[1],0666);
	ERROR_CHECK(ret,-1,"chmod");
	return 0;
}
