#include <iostream>
using std::cout;
using std::endl;



//互斥锁 功能：我锁上，你就不能开，我开了，你才能上锁
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

int main(void)
{
	MutexLock lock;
	lock.lock();
	lock.unlock();
	return 0;
}
