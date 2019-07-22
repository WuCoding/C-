#include <func.h>
//用stat函数来获得一个文件的stat结构体信息
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,2);
	int ret;
	struct stat buf;//用来接stat函数返回的结构体的内容
	//stat成功返回0 失败返回-1
	ret=stat(argv[1],&buf);
	ERROR_CHECK(ret,-1,"stat");
	printf("%ld %x %ld %s %s %ld %s\n",buf.st_ino,\
			buf.st_mode,buf.st_nlink,\
			getpwuid(buf.st_uid)->pw_name,\
			getgrgid(buf.st_gid)->gr_name,\
			buf.st_size,ctime(&buf.st_mtime));
	return 0;
}
