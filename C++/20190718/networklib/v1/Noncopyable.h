#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{

class Noncopyable
{
	protected:
		//防止直接创建该类的对象
		//构造函数
		Noncopyable()
		{}
		//析构函数
		~Noncopyable()
		{}

		//将复制构造函数删除
		Noncopyable(const Noncopyable &)=delete;
		//将赋值操作运算符删除
		Noncopyable& operator=(const Noncopyable &)=delete;
};

}//end of namespace wd

#endif


