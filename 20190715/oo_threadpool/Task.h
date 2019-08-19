#pragma once

namespace wd
{

//抽象类
class Task
{
public:
	//纯虚函数
	virtual void process()=0;

	//析构函数设为虚函数
	virtual ~Task()
	{}
};

}//end of namespace wd
