#include <func.h>
//删除文件夹rmdir
int main(int argc,char* argv[])
{
	ARGS_CHECK(argc,2);
	int ret;
	ret=rmdir(argv[1]);
	ERROR_CHECK(ret,-1,"rmdir");
	return 0;
}

