#include <iostream>
using std::cout;
using std::endl;

class MutexLock
{
	public:
		//构造函数
		MutexLock()//初始化一把锁 0为没上锁 1为上锁
		: _flag(0)
		{
			cout<<"创建锁成功"<<endl;
		}
		void lock()
		{
			while(_flag==1)//如果锁已被锁上
			{
				;
			}
			//从while语句出来表示锁已经被打开
			//进行上锁
			_flag=1;
			cout<<"上锁成功"<<endl;
		}
		void unlock()
		{
			_flag=0;
			cout<<"解锁成功"<<endl;
		}
	private:
		int _flag;
};
//条件变量功能：发信号，通知所有，通知一个
class Condition
{
	public:
		//构造函数，创建一个信号量
		Condition()
		: _allflag(0)       //0 没有唤醒，1唤醒
		, _singleflag(0)
		{
			cout<<"创建信号量成功"<<endl;
		}
		//睡在信号量上
		void wait()
		{
			//先解锁
			_lock.unlock();
			//等待信号，没有信号
			cout<<"wait成功"<<endl;
			while(_allflag==0||_singleflag==0)
			{
				;
			}

			//此时有信号来唤醒
			//此时是全部唤醒
			if(_allflag==1)
			{
				_lock.lock();
			}
			//此时是单个唤醒
			if(_singleflag==1)
			{
				//先上锁
				_lock.lock();
				//将信号改变
				_singleflag=0;
			}
		}
	private:
			MutexLock _lock;
			int _allflag;//全部唤醒信号
			int _singleflag;//单个唤醒信号


};




int main(void)
{
	MutexLock lock;
	lock.lock();
	lock.unlock();
	return 0;
}
