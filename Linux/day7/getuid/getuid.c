#include <func.h>

int main()
{
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n"
		,getuid(),getgid(),geteuid(),getegid());
	//分别获得当前进程：用户id，组id，有效用户id，有效组id
	
	return 0;
}
