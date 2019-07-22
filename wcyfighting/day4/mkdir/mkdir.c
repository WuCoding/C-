#include <func.h>
//创建文件夹mkdir
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int ret;
	//创建文件夹实际受掩码影响创建0777实际是0775
	ret=mkdir(argv[1],0777);
	ERROR_CHECK(ret,-1,"mkdir");
	return 0;
}

