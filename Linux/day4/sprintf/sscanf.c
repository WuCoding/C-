#include <stdio.h>
#include <string.h>

typedef struct{
	int num;
	float score;
	char name[20];
}Stu_t;

int main()
{
	char buf[128]="1001 98.50 lele";
	Stu_t student={0};
	sscanf(buf,"%d%f%s",&student.num,&student.score,student.name);
	printf("%d %5.2f %s\n",student.num,student.score,student.name);
	return 0;
}

