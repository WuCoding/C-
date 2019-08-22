#pragma once

#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;




#if 0
timerfd是Linux提供的一个定时器接口。这个接口基于文件描述符，通过文件描述符的
可读事件进行超时通知，所以能够被用于select/poll/epoll的应用场景。timerfd是
linux内核2.6.25版本中加入的接口。
#include <sys/timerfd.h>

>>-----------------------------------------------------------------------------<<
int timerfd_create(int clockid, int flags);
功能：
	>该函数生成一个定时器对象，返回与之关联的文件描述符。
参数详解：
	>clockid:可设置为
		>CLOCK_REALTIME：相对时间，从1970.1.1到目前的时间。
		>更改系统时间 会更改获取的值，它以系统时间为坐标。
		>CLOCK_MONOTONIC：绝对时间，获取的时间为系统重启到现在的时间，
		>更改系统时间对齐没有影响。
	>flags: 可设置为
		>TFD_NONBLOCK（非阻塞），
		>TFD_CLOEXEC（同O_CLOEXEC）
		>0 linux内核2.6.26版本以上都指定为0
>>------------------------------------------------------------------------------<<
int timerfd_settime(int fd, int flags,
		const struct itimerspec *new_value,struct itimerspec *old_value);
功能：
	>该函数能够启动和停止定时器
参数详解：
	>fd: timerfd对应的文件描述符
	>flags: 
		>0 表示是相对定时器
		>TFD_TIMER_ABSTIME 表示是绝对定时器
	>new_value:设置超时时间，如果为0则表示停止定时器。
	>old_value:一般设为NULL, 不为NULL,则返回定时器这次设置之前的超时时间
struct timespec{
	time_t tv_sec;			/*Seconds*/秒
	long tv_nsec;			/*Nanoseconds*/纳秒
};

struct itimerspec{
	struct timespec it_interval;	/*Interval间隔 for periodic周期的 timer定时器*/
	struct timespec it_value;	/*Initial最初的 expiration满期、截止*/
};
操作：
	>read：
		>读取缓冲区中的数据，其占据的存储空间为sizeof(uint64_t)，表示超时次数。
	>select/poll/epoll：
		>当定时器超时时，会触发定时器相对应的文件描述符上的读操作，IO复用操作会返回，
		>然后再去对该读事件进行处理。
#endif


namespace wd
{

class Timerfd
{
	public:
		using TimerCallback=function<void()>;

		Timerfd(int initialTime,int intervalTime,TimerCallback && cb);

		void start();
		void stop();

	private:
		int createTimerfd();
		void setTimerfd(int initialTime,int intervalTime);
		void handleRead();
	private:
		int _fd;
		int _initialTime;
		int _intervalTime;
		TimeCallback _cb;
		bool _isStarted;
};
}//end of namespace wd
