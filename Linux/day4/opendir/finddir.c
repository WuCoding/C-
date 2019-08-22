#include <func.h>

int printDir(char *path,int width)
{
	DIR *dir;
	dir=opendir(path);
	ERROR_CHECK(dir,NULL,"opendir");
	struct dirent *p;
	//路径拼接
	char tmpPath[1024]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
			continue;
		}
		printf("%*s%s\n",width," ",p->d_name);
		//判断p是否为一个目录文件
		if(4==p->d_type){
			sprintf(tmpPath,"%s%s%s",path,"/",p->d_name);
			printDir(tmpPath,width+4);
		}
		//是---->调用printDir打印p目录文件下的信息
	}
	closedir(dir);
}

int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	printDir(argv[1],4);
}

