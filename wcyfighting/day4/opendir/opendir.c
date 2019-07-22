#include <func.h>

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	DIR* dir;
	//打开目录，目录文件存储的是目录下文件的dirent结构体信息，但是这些结构体不是连续存储的是类似用链表存储
	dir=opendir(argv[1]);
	struct dirent *p;
	//readdir函数每读一个文件的dirent信息，就自动偏移指向下一个文件的dirent信息，读到结尾返回 NULL
	while((p=readdir(dir))!=NULL)
	{
		printf("%d %d %s\n",p->d_reclen,p->d_type,p->d_name);//文件名长度，文件类型（0~15），文件名
	}
	closedir(dir);
}


