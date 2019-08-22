#pragma once

namespace wd
{

class Noncopyable
{
	protected:
		//构造函数
		Noncopyable()
		{}
		//析构函数
		~Noncopyable()
		{}

		Noncopyable(const Noncopyable &)=delete;
		Noncopyable & operator=(const Noncopyable &)=delete;

};

}//end of namespace wd
