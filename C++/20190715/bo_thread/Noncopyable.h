#pragma once

namespace wd
{

class Noncopyable
{
	protected:
		//将构造函数和析构函数都设为protected权限，防止直接
		//创建该类型的对象
		
		//构造函数
		Noncopyable()
		{}
		//析构函数
		~Noncopyable()
		{}

		//将复制构造函数删除
		Noncopyable(const Noncopyable&)=delete;
		//将赋值运算符重载函数删除
		Noncopyable & operator=(const Noncopyable&)=delete;
};
}//end of namespace wd

