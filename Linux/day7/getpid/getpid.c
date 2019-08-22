#include <func.h>

int main()
{
	pid_t pid,ppid;//pid_t类型就是int

	pid=getpid();//获得自己进程的id
	ppid=getppid();//获得父进程的id

	printf("pid=%d,ppid=%d\n",pid,ppid);
	return 0;
}
