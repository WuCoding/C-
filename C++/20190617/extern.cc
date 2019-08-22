#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
//c和c++混合编程
#ifdef __cplusplus //该宏只会在c++的编译器中定义
extern "C"
{
#endif
	int add(int x,int y)
	{
		return x+y;
	}
#ifdef __cplusplus
}//end of extern "C"
#endif



