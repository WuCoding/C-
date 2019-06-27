#pragma once

//PIMPL设计模式
//优点：
//	1. 可以实现信息隐蔽
//	2. 可以降低编译依赖，以最低的成本完成库的平滑升级

class Line//class默认为private
{
	class LineImpl;//该内含类是private
	
	public:
		//类的构造函数
		Line(int x1,int y1,int x2,int y2);
		//类的析构函数
		~Line();
		//类的打印函数
		void printLine() const;

	private:
		//类的数据成员
		LineImpl *_pimpl;//内含类的指针
};


