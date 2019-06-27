 ///
 /// @file    log4cpp2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-22 11:06:42
 ///

#include <log4cpp/Category.hh> //日志记录器
#include <log4cpp/Priority.hh>  //优先级
#include <log4cpp/OstreamAppender.hh>  //用终端输出
#include <log4cpp/PatternLayout.hh>  //自定义格式
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
//                > BasicLayout
//                > PatternLayout


//setAppender() 设置目的地
//addAppender() 添加目的地

#include <iostream>
using std::cout;
using std::endl;

using namespace log4cpp;
 
int main(void)
{
	//-------------------------------------布局设计-----------------------------------------------
	//pattern模式、样品、图案  layout布局、设计 自定义格式
	PatternLayout * ptnLayout = new PatternLayout();
	//conversion转换、变换 pattern模式、样品、图案
	ptnLayout->setConversionPattern("%d [%p] %m%n");//%d日期 %p优先级将优先级用[]括起来 %m日志内容 %n换行
	//-----------------------------------用设计的布局--------------------------------------------
	//输出流，设置日志输出的地方
	OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender", &cout);//&cout表示输出到 标准输出流 第一个参数为设定的名字，第二个参数为流的引用
	//设置布局
	ostreamAppender->setLayout(ptnLayout);
	//------------------------------------设置种类-----------------------------------------------
	//category种类、分类  获取日志记录器
	Category & root = Category::getRoot();//拿到一个category实例
	//设置输出目的地
	root.setAppender(ostreamAppender);
	//设置日志记录器本身的优先级
	root.setPriority(Priority::DEBUG);//设置日志记录器的级别，如果日志级别大于等于日志记录器级别，才会被记录
 
	//设置完毕，开始输出具体的日志信息
	//alert警告、警戒
	root.alert("alert message");//一条日志的级别
	//crit暴击、评判
	root.crit("crit message");
	//debug调试、除错
	root.debug("debug message");
	//error误差错误
	root.error("error message");
	//emerg紧急事件
	root.emerg("emerg message");
	//info信息情报
	root.info("info message");
	//fatal致命的、毁灭性的
	root.fatal("fatal message");
	//warn警告、提醒
	root.warn("warn message");
	
	
	//进行资源回收，调用Category类的静态函数
	//shutdown关机、停工
	Category::shutdown();//回收资源

	return 0;
}
