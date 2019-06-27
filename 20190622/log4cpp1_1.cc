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
//输出到标准输出
int main(int argc, char** argv) {
	//---------------------------------基础布局来设置布局----------------------------------------
	//输出到标准输出 console控制台、操作台 append附加、贴上
	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);//&std::cout 表示输出到 标准输出流
	//layout布局、设计 
	appender1->setLayout(new log4cpp::BasicLayout());//BasicLayout()基础布局
	
	//-------------------------------------设置种类----------------------------------------------
	//category种类  日志记录器
	log4cpp::Category& root = log4cpp::Category::getRoot();
	//priority优先权
	root.setPriority(log4cpp::Priority::WARN);//设置日志记录器的等级
	root.addAppender(appender1);//添加日志记录器的输出目的地为appender1
	
	// use of functions for logging messages 使用函数记录信息
	root.error("root error");
	root.info("root info");
	// printf-style for logging variables 记录变量的输出形式
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages 使用流来记录信息
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	// or this way: 或者这种方法
	root.errorStream() << "Another streamed error";

	return 0;
}

