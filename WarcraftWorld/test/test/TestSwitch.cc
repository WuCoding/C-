#include "test.h"
        int add1()
	{
		return 10;
	}
	int add2()
	{
		return 20;
	}
	int add3()
	{
		return 30;
	}
	int add4()
	{
		return 40;
	}
	int add5()
	{
		return 50;
	}

	int Mycreate(int m)
	{
		int n;
		switch (m){
			case 1:
				n=add1();
				break;
			case 2:
				n=add2();
				break;
			case 3:
				n=add3();
				break;
			case 4:
				n=add4();
				break;
			case 5:
				n=add5();

		}
		return n;
	}


int test()
{

	cout<<Mycreate(1)<<endl;
	cout<<Mycreate(2)<<endl;
	cout<<Mycreate(3)<<endl;
	cout<<Mycreate(4)<<endl;
	cout<<Mycreate(5)<<endl;

	return 0;
}
int main(void)
{
	test();
}
				
