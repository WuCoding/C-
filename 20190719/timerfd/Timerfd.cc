#include "Timerfd.h"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using std::cout;
using std::endl;

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

//构造函数 参数：初始时间、间隔时间、回调函数
//构建一个timerfd描述符，初始化初始时间、间隔时间和回调函数，初始化开始标志位
Timerfd::Timerfd(int initialTime,int intervalTime,TimerCallback && cb)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _cb(std::move(cb))
, _isStarted(false)
{}

void Timerfd::start()
{
	_isStarted=true;

	//将该timerfd描述符加入监控序列
	struct pollfd pfd;
	pfd.fd=_fd;
	pfd.events=POLLIN;//检测该描述符的可读状态

	//设置该timerfd的初始时间和间隔时间
	setTimerfd(_initialTime,_intervalTime);

	//进入循环
	while(_isStarted){//如果_isStarted为true
		//已经就绪的描述符数量
		int nready=::poll(&pfd,1,5000);//等待时间为5s
		if(nready==-1 && errno ==EINTR){//遇到中断
			continue;
		}else if(nready==-1){//poll函数执行出错
			return;
		}else if(nready==0){//获得就绪描述符超时
			printf(">>poll timeout!\n");
		}else{//获得已经就绪的描述符
			if(pfd.revents & POLLIN){//监控的是该描述符的可读事件
				//执行读操作
				handleRead();
				if(_cb){//如果已经注册回调函数，执行回调函数
					_cb();
				}
			}
		}
	}
}

void Timerfd::stop()
{
	if(_isStarted){//如果已经开始监控该timerfd
		_isStarted=false;
		//设置为0，表示停止该计时器
		setTimerfd(0,0);
	}
}

//创建一个timerfd描述符
int Timerfd::createTimerfd()
{
	//调用timefd_create创建一个timerfd描述符，设置为相对时间
	int fd=::timerfd_create(CLOCK_REALTIME,0);
	if(fd==-1){
		perror(">>timefd_create");
	}
	return fd;
}

//设置初始时间和时间间隔
void Timerfd::setTimerfd(int initialTime,int intervalTime)
{
	//该结构体中存有初始时间和间隔时间
	struct itimerspec value;
	//设置初始时间的秒数
	value.it_value.tv_sec=initialTime;
	//设置初始时间的纳秒数
	value.it_value.tv_nsec=0;

	//设置间隔时间的秒数
	value.it_interval.tv_sec=intervalTime;
	//设置间隔时间的纳秒数
	value.it_interval.tv_nsec=0;

	//对该timerfd进行设置
	int ret=::timerfd_settime(_fd,0,&value,nullptr);
	if(ret==-1){
		perror(">> timerfd_settime");
	}
}

//当timerfd可读时进行读操作，实际读取出来的是该计时器的超时次数
void Timerfd::handleRead()
{
	uint64_t howmany;
	//获得该计时器的超时次数
	int ret=::read(_fd,&howmany,sizeof(uint64_t));
	if(ret!=sizeof(howmany)){
		perror(">>read");
	}
}
}//end of namespace wd
	


		


