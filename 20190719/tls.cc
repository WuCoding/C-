#include <pthread.h>
#include <errno.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

//线程局部存储
//__thread变量

int gNumber=10;
__thread int number=0;
//__thread string s1="hello";

void *threadfunc1(void *arg)
{
	printf("threadfunc1:&errno=%p\n",&errno);
	printf("threadfunc1:&gNumber=%p\n",&gNumber);

	number=1;
	printf("threadfunc1:number=%d\n",number);
	printf("threadfunc1:&number=%p\n",&number);

	return nullptr;
}

void *threadfunc2(void *arg)
{
	printf("threadfunc2:&errno=%p\n",&errno);
	printf("threadfunc2:&gNumber=%p\n",&gNumber);

	//number=2;
	printf("threadfunc2:number=%d\n",number);
	printf("threadfunc2:&number=%p\n",&number);
	
	return nullptr;
}

int main(void)
{
	printf("mainthread:&errno=%p\n",&errno);
	printf("mainthread:&gNumber=%p\n",&gNumber);

	number=3;
	printf("mainthread:number=%d\n",number);
	printf("mainthread:&number=%p\n",&number);

	pthread_t pthid1,pthid2;

	pthread_create(&pthid1,nullptr,threadfunc1,nullptr);
	pthread_create(&pthid2,nullptr,threadfunc2,nullptr);

	pthread_join(pthid1,nullptr);
	pthread_join(pthid2,nullptr);

	return 0;
}
