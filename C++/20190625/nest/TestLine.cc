#include "Line.h"

#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
	//内部实际是调用LineImpl类的成员实现的，但对外界不可见
	Line line(1,2,3,4);
	line.printLine();
	return 0;
}
