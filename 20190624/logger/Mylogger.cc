#include "Mylogger.h"

#include <log4cpp/Priority.hh>//优先级
#include <log4cpp/OstreamAppender.hh>//标准输出流作为输出目的地
#include <log4cpp/FileAppender.hh>//文件作为输出目的地
#include <log4cpp/PatternLayout.hh>//自定义格式

#include <iostream>
using std::cout;
using std::endl;
//这里放着Mylogger类的函数实现
namespace wd
{
	//对静态数据成员在类外进行赋值
	Mylogger * Mylogger::_pInstance=nullptr;

	//对单例类对象创建函数
	Mylogger* Mylogger::getInstance()
	{
		if(_pInstance==nullptr){//此时对象未创建
			_pInstance=new Mylogger();
		}
		return _pInstance;
	}

	//对单例类对像的销毁函数
	void Mylogger::destroy()
	{
		if(_pInstance!=nullptr){//对象存在未被销毁
			delete _pInstance;
			_pInstance=nullptr;
		}
	}
	
	//error日志输出函数
	void Mylogger::error(const char * msg)
	{
		_root.error(msg);//日志记录器
	}

	//warn日志输出函数
	void Mylogger::warn(const char * msg)
	{
		_root.warn(msg);//日志记录器
	}

	//info日志输出函数
	void Mylogger::info(const char * msg)
	{
		_root.info(msg);//日志记录器
	}

	//debug日志输出函数
	void Mylogger::debug(const char * msg)
	{
		_root.debug(msg);//日志记录器
	}

	//Mylogger类的构造函数
	Mylogger::Mylogger()
	: _root(Category::getRoot().getInstance("root"))
	{
		//设置格式1
		PatternLayout * ptn1=new PatternLayout();
		ptn1->setConversionPattern("%d [%p] %m%n");//%d日期 %p优先级 %m日志信息

		//设置格式2
		PatternLayout * ptn2=new PatternLayout();
		ptn2->setConversionPattern("%d [%p] %m%n");

		//创建输出目的地1，标准输出
		OstreamAppender *ostreamAppender=new OstreamAppender("ostreamAppender",&cout);//第一个参数为，为目的地指定的名字
		//设置输出到目的地的格式
		ostreamAppender->setLayout(ptn1);

		//创建输出目的地2，输出到文件
		FileAppender * fileAppender=new FileAppender("fileAppender","wangdao.log");//第一个参数为，为目的地指定的名字，第二个参数为要输出的文件名
		//设置输出到目的地的格式
		fileAppender->setLayout(ptn2);

		//为日志记录器添加目的地
		_root.addAppender(ostreamAppender);
		_root.addAppender(fileAppender);
		//为日志记录器设置优先级，只有比日志记录器优先级高的日志才会被记录
		_root.setPriority(Priority::DEBUG);

		cout<<"Mylogger()"<<endl;
	}

	//Mylogger类的析构函数
	Mylogger::~Mylogger()
	{
		//Category类型的资源回收
		Category::shutdown();

		cout<<"~Mylogger()"<<endl;
	}
}//end of namespace wd

	





































