///
/// @file    log4cpp1.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2019-06-22 10:59:15
///

#include <iostream>
using std::cout;
using std::endl;

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
//输出到文件
int main(int argc, char** argv) {
	//----------------------------------设置布局为基础布局---------------------------------------
	//输出到文件中 default系统默认值
	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
	//layout布局、设计  设置布局
	appender2->setLayout(new log4cpp::BasicLayout());//BasicLayout()基础布局
	//-------------------------------------设置种类---------------------------------------------
	//category种类 instance实例、情况 getinstance获得实例
	log4cpp::Category& root = log4cpp::Category::getInstance(std::string("root"));//日志记录器
	root.addAppender(appender2);//添加日志记录器的输出目的地

	// use of functions for logging messages 使用函数记录信息
	root.error("root error");
	root.warn("root warn");

	// use of streams for logging messages 使用流来记录信息
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::WARN << "Streamed root warn";

	return 0;
}

