#pragma once

#include <log4cpp/Category.hh>//日志记录器

using namespace log4cpp;
//用单例类来实现自定义的日志类
//这里是声明，实现是在Mylogger.cc里实现的
namespace wd
{
	class Mylogger
	{
		public:
			//单例创建对象函数
			static Mylogger * getInstance();
			//单例销毁对象函数
			static void destroy();

			//输出error日志函数
			void error(const char * msg);
			//输出warn日志函数
			void warn(const char * msg);
			//输出info日志函数
			void info(const char * msg);
			//输出debug日志函数
			void debug(const char * msg);

		private:
			//单例类中，将构造和析构全都隐藏起来，防止外界调用产生栈对象
			Mylogger();
			~Mylogger();
		private:
			//存储单个对象在堆内存的地址
			static Mylogger* _pInstance;
			Category & _root;//日志记录器，将日志信息输出到多个目的地
	};
}//end of namespace wd
#define prefix(msg) string("[").append(__FILE__)\
	.append(":").append(__FUNCTION__)\
	.append(":").append(std::to_string(__LINE__))\
	.append("]").append(msg).c_str()

#define LogError(msg) wd::Mylogger::getInstance()->error(prefix(msg))
#define LogWarn(msg) wd::Mylogger::getInstance()->warn(prefix(msg))
#define LogInfo(msg) wd::Mylogger::getInstance()->info(prefix(msg))
#define LogDebug(msg) wd::Mylogger::getInstance()->debug(prefix(msg))
