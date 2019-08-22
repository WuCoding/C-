#include <func.h>
 
int main()
{
	FILE *fp=fopen("file","rb+");
	
	int fd=fileno(fp);
	write(fd,"hello",5);
	fclose(fp);
	return 0;
}
