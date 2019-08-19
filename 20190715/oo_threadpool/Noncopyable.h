#pragma once

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable()
	{}
	~Noncopyable()
	{}

	//将复制构造函数删除
	Noncopyable(const Noncopyable&)=delete;
	//将该类型的赋值运算符删除
	Noncopyable & operator=(const Noncopyable&)=delete;

};

}//end of namespace wd
