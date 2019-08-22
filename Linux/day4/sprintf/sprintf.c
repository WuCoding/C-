#include <stdio.h>
#include <string.h>
typedef struct{
	int num;
	float score;
	char name[20];
}Stu_t;

int main()
{
	Stu_t student={1001,98.5,"lele"};
	char buf[128];

	memset(buf,0,sizeof(buf));
	sprintf(buf,"%d %5.2f %s",student.num,student.score,student.name);
	printf("%s\n",buf);
	return 0;
}
