#include "test.h"
class GameTime
{
	public:
		//单例对象创建函数
		static GameTime * getInstance()
		{
			if(nullptr==_pInstance){
				//进行初始化
				_pInstance=new GameTime();
			}
			return _pInstance;
		}
		//单例对象销毁函数
		static void destroy()
		{
			if(_pInstance!=nullptr){
				//单例对象存在
				delete _pInstance;
				_pInstance=nullptr;
			}
		}
		//打印时间函数
		void showTime() const
		{
			cout<<_hour<<":"<<_minute;
		}
		//更新时间
		void updateTime()
		{
			if(50==_minute){
				_hour+=1;
				_minute=0;
			}else{
				_minute+=10;
			}
		}
		//重置时间
		void reset()
	       	{ 
			_hour = 0; 
			_minute = 0; 
		}
	private:
		//私有化构造函数
		GameTime(size_t hour = 0, size_t minute = 0)
		: _hour(hour)
		, _minute(minute)
		{}
	private:
		//数据成员
		//指向单例对象在堆空间的地址
		static GameTime * _pInstance;
		size_t _hour;
		size_t _minute;
};
//初始化类中static数据
GameTime* GameTime::_pInstance=nullptr;

int test0()
{
	GameTime* time=GameTime::getInstance();
	GameTime* time2=GameTime::getInstance();

	cout<<time<<endl<<time2<<endl;

	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->updateTime();
	time->showTime();
	cout<<endl;
	
	time->reset();
	time->showTime();
	cout<<endl;
	
	return 0;
}
int main(void)
{
	test0();
}






	
