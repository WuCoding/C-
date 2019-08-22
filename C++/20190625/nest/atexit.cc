#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

void display()
{
	cout<<"display()"<<endl;
}

int main(void)
{
	cout<<"enter main..."<<endl;

	atexit(display);
	atexit(display);
	atexit(display);

	cout<<"exit main..."<<endl;
	return 0;
}

