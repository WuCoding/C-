#include <func.h>
//
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	DIR* dir;
	dir=opendir(argv[1]);
	struct dirent *p;
    p->d_type
	//记录偏移位置
	off_t pos;
	while((p=readdir(dir))!=NULL)
	{
		printf("%ld %d %d %s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
		if(0==strcmp(p->d_name,"file"))
		{
			//记录下file文件的偏移位置(磁盘地址)
			pos=telldir(dir);
		}
	}
	printf("-----------------------------------\n");
	printf("pos=%ld\n",pos);
	//重新将指针偏移到记录下的位置
	seekdir(dir,pos);
	//偏移指针后重新读出当前指针指向的文件
	p=readdir(dir);
	printf("%d %d %s\n",p->d_reclen,p->d_type,p->d_name);	
	closedir(dir);
}


