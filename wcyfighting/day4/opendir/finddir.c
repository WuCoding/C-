#include <func.h>
//传入一个路径对该路径进行深度优先遍历

int printDir(char* path,int width)
//width表示名字前面要打印的空格数
{
	DIR* dir;
	//打开当前路径的目录文件
	dir=opendir(path);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	//路径拼接字符串
	char tmpPath[1024]={0};
	//依次遍历当前目录下的文件信息
	while((p=readdir(dir))!=NULL)
	{
		//如果文件是.或..目录则不进行递归，否则会陷入死循环
		if(0==strcmp(p->d_name,".")||0==strcmp(p->d_name,".."))
		{
			continue;
		}
		//打印文件名（包括前面的多个空格）
		printf("%*s%s\n",width,"",p->d_name);
		//如果是目录文件则进行递归
		if(4==p->d_type)
		{
			//进行路径拼接
			sprintf(tmpPath,"%s%s%s",path,"/",p->d_name);
			printDir(tmpPath,width+4);
		}
	}
	closedir(dir);
}
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	puts(argv[1]);
	printDir(argv[1],0);
}


