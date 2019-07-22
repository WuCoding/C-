#pragma once

namespace wd
{
//防止赋值、复制的类，继承该类的派生类都无法进行复制构造和赋值操作
//因为一旦派生类执行赋值或复制构造函数都需要先调基类的该函数来赋值或
//复制构造该派生类的对象中的基类部分，所以派生类也无法进行该操作
class Noncopyable
{
	protected:
		//构造函数
		Noncopyable()
		{}
		//析构函数
		~Noncopyable()
		{}

		//删除复制构造函数
		Noncopyable(const Noncopyable&)=delete;
		//删除赋值运算符重载函数
		Noncopyable & operator=(const Noncopyable &)=delete;
};
}//end of namespace wd
