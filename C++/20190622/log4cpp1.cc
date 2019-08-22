///
/// @file    log4cpp1.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-06-22 10:59:15
///

#include <iostream>
using std::cout;
using std::endl;

#include "log4cpp/Category.hh"//日志记录器
#include "log4cpp/Appender.hh"//输出目的地
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"//布局设置
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"//优先级
//> 日志系统的抽象
//     > 日志来源（日志记录器）
//           > Category  //可以把一条信息输出到多个目的地
//     > 日志级别
//           > Priority   //优先级
//                > EMERG
//                > FATAL
//                > ALERT
//                > CRIT
//                > ERROR
//                > WARN
//                > NOTICE
//                > INFO
//                > DEBUG
//                > NOTSET
//     > 日志目的地
//           > Appender
//                > OstreamAppender  //标准输出流
//                > FileAppender   //不断地往文件里写内容，造成大文件不方便阅读
//                > RollingFileAppender   //限制文件大小
//     > 日志格式
//           > Layout //布局
//                > BasicLayout  //基础格式
//                > PatternLayout //自己设置日志格式

int main(int argc, char** argv) {
	//输出到标准输出 console控制台、操作台 append附加、贴上
	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);//&std::cout 表示输出到 标准输出流
	//layout布局、设计 
	appender1->setLayout(new log4cpp::BasicLayout());//BasicLayout()基础布局
	
	
	//输出到文件中 default系统默认值
	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	appender2->setLayout(new log4cpp::BasicLayout());
	//category种类  日志记录器
	log4cpp::Category& root = log4cpp::Category::getRoot();
	//priority优先权
	root.setPriority(log4cpp::Priority::WARN);//设置日志记录器的优先级，只有日志优先级大于等于日志记录器优先级，才会被记录下来
	root.addAppender(appender1);//添加日志记录器的输出目的地为appender1
	
	//category种类 instance实例、情况 getinstance获得实例
	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));//获得实例
	sub1.addAppender(appender2);//添加日志记录器的输出目的地为appender2

	// use of functions for logging messages 使用函数记录信息
	root.error("root error");//日志等级
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables 记录变量的输出形式
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages 使用流来记录信息
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way: 或者这种方法
	root.errorStream() << "Another streamed error";

	return 0;
}

