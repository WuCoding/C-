#pragma once

namespace wd
{

//禁止拷贝类型
class Noncopyable
{
	protected:
		//将构造函数和析构函数设为protected权限
		//防止创建出Noncopyable类型的对象
		Noncopyable()
		{}
		~Noncopyable()
		{}

		//将复制构造函数删除
		Noncopyable(const Noncopyable&)=delete;
		//将赋值运算符重构函数删除
		Noncopyable & operator=(const Noncopyable &)=delete;
};
}//end of namespace wd
