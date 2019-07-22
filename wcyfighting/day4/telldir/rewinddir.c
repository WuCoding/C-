#include <func.h>
//
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	DIR* dir;
	dir=opendir(argv[1]);
	struct dirent *p;
	//记录偏移位置
	off_t pos;
	while((p=readdir(dir))!=NULL)
	{
		printf("%d %d %s\n",p->d_reclen,p->d_type,p->d_name);
	}
	printf("-----------------------------------\n");
	//将目录中的指针偏移到开头
	rewinddir(dir);
	//偏移指针后重新读出当前指针指向的文件
	p=readdir(dir);
	printf("%d %d %s\n",p->d_reclen,p->d_type,p->d_name);	
	closedir(dir);
}


