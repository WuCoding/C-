 ///
 /// @file    log4cpp3.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-22 11:06:42
 ///

#include <log4cpp/Category.hh>//日志记录器
#include <log4cpp/Priority.hh>//日志优先级
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>  //日志输出目的地为文件，这个可以一直往文件里写，而回卷文件可以设置大小
#include <log4cpp/RollingFileAppender.hh>  //日志输出目的地为回卷文件，小文件好处理
#include <log4cpp/PatternLayout.hh>
//> 日志系统的抽象
//     > 日志来源（日志记录器）
//           > Category   本身拥有一个优先级      //可以把一条信息输出到多个目的地
//           > 每条日志拥有自己的优先级
//           > 当日志优先级大于等于category优先级时，这条日志就会被记录；否则被忽略
//     > 日志级别
//           > Priority   //优先级
//                > ERROR
//                > WARN
//                > DEBUG
//     > 日志目的地
//           > Appender
//                > OstreamAppender
//                > FileAppender   //不断地往文件里写内容，造成大文件不方便阅读
//                > RollingFileAppender   //限制文件大小
//     > 日志格式
//           > Layout //布局
//                > BasicLayout//基础布局
//                > PatternLayout//自己设置布局
//     > 产生的日志文件最多只有1个G
//           > 利用回卷文件
//                > 32个文件
//                > 1个文件占据的空间大小是32M //当32个文件已经创建，再写入时，则将最
//                                             //先的文件删除，创建新的文件来继续写



#include <iostream>
using std::cout;
using std::endl;

using namespace log4cpp;
 
int main(void)
{
	//------------------------------------布局设计---------------------------------------------
	PatternLayout * ptnLayout1 = new PatternLayout();//%d日期 %p优先级 %m日志信息
	ptnLayout1->setConversionPattern("%d [%p] %m%n");//一个PatternLayout对应一个目的地，不能一个PatternLayout对应多个目的地

	PatternLayout * ptnLayout2 = new PatternLayout();
	ptnLayout2->setConversionPattern("%d [%p] %m%n");

	PatternLayout * ptnLayout3 = new PatternLayout();
	ptnLayout3->setConversionPattern("%d [%p] %m%n");

	//--------------------------------设置为设计的布局-----------------------------------------
	//输出到标准输出 日志输出目的地为标准输出
	OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &cout);
	ostreamAppender->setLayout(ptnLayout1);
	//输出到指定文件 日志输出目的地为指定文件
	FileAppender * fileAppender = new FileAppender("fileAppender", "wangdao.log");//第一个参数是为目的地起的名字，第二个参数为文件名字
	fileAppender->setLayout(ptnLayout2);
	//循环输出到文件 日志输出目的地为rolling文件
	RollingFileAppender * rollingFileAppender = new 
		RollingFileAppender("rollingfileAppender",//为日志目的地设名字
			"rollingwangdao.log",//为回卷文件设置文件名
			5 * 1024,//设置文件大小 5 k
			2);//设置回卷文件产生的个数
	rollingFileAppender->setLayout(ptnLayout3);

	//------------------------------------设置种类-----------------------------------------------
	//category日志记录器是可以把信息输出到多个地方的，一开始用setAppender，后面用addAppender
	Category & root = Category::getRoot();
	root.setAppender(ostreamAppender);
	root.addAppender(fileAppender);
	root.addAppender(rollingFileAppender);
	//设置category日志记录器优先级
	root.setPriority(Priority::DEBUG);//日志记录器的级别
 
	int cnt = 100;
	while(cnt--) {
		root.alert("alert message");//一条日志的级别
		root.crit("crit message");
		root.debug("debug message");
		root.error("error message");
		root.emerg("emerg message");
		root.info("info message");
		root.fatal("fatal message");
		root.warn("warn message");
	}

	Category::shutdown();//回收资源

	return 0;
}
