#include <stdio.h>

//C语言不支持函数重载
int add(int x,int y)
{
	return x+y;
}

int add(int x,int y,int z)
{
	return x+y+z;
}

int main(void)
{
	int  a=3,b=4,c=5;
	add(a,b);
	add(a,b,c);

	return 0;
}
