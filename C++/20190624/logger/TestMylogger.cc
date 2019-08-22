#include "Mylogger.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//对类成员函数的调用测试
void test0()
{
	wd::Mylogger::getInstance()->error("error message");
	wd::Mylogger::getInstance()->warn("warn message");
	wd::Mylogger::getInstance()->info("info message");
	wd::Mylogger::getInstance()->debug("debug message");
}

//对输出函数名、文件名、行号（只能输出__LINE__所在行的行号）的测试
void test1()
{
	cout<<__func__<<endl;
	cout<<__FILE__<<endl;
	cout<<__LINE__<<endl;
}

#if 0
#define prefix(msg) string("[").append(__FILE__)\
	.append(":").append(__FUNCTION__)\
	.append(":").append(std::to_string(__LINE__))\
	.append("]").append(msg).c_str()

#define LogError(msg) wd::Mylogger::getInstance()->error(prefix(msg))
#define LogWarn(msg) wd::Mylogger::getInstance()->warn(prefix(msg))
#define LogInfo(msg) wd::Mylogger::getInstance()->info(prefix(msg))
#define LogDebug(msg) wd::Mylogger::getInstance()->debug(prefix(msg))
#endif

void test2()
{
	wd::Mylogger::getInstance()->error(prefix("error message"));
	wd::Mylogger::getInstance()->warn(prefix("warn message"));
	wd::Mylogger::getInstance()->info(prefix("info message"));
	wd::Mylogger::getInstance()->debug(prefix("debug message"));
}

void test3()
{
	int number=1;
	LogError("error message");

	LogWarn("warn message");
	LogInfo("info message");
	LogDebug("debug message");
}
int main(void)
{
	test0();
	test1();
	test2();
	test3();

	wd::Mylogger::getInstance()->destroy();
	return 0;
}
























