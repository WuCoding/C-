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

	//删除复制构造函数
	Noncopyable(const Noncopyable&)=delete;
	//删除赋值运算符
	Noncopyable & operator=(const Noncopyable &)=delete;
};

}//end of namespace wd
