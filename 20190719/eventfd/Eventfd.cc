#include "Eventfd.h"

#include <unistd.h>
#include <poll.h>
#include <sys/eventfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

//构造函数
Eventfd::Eventfd(EventCallback &&cb)
: _fd(createEventfd())
, _cb(std::move(cb))
, _isStarted(false)
{}

#if 0
头文件：
	#include <sys/poll.h> 
函数原型：
	int poll(struct pollfd *ufds, unsigned int nfds, int timeout); 
数据结构：
	struct pollfd {
		int fd;        	/* 文件描述符 */
		short events; 	/* 等待的事件 */
		short revents; 	/* 实际发生了的事件 */
	};
	
	typedef unsigned long   nfds_t;
参数说明:
	ufds：	
		>是一个struct pollfd结构类型的数组，用于存放需要检测其状态的Socket描述符；
		>每当调用这个函数之后，系统不会清空这个数组，操作起来比较方便；特别是对于 
		>socket连接比较多的情况下，在一定程度上可以提高处理的效率；这一点与select()
		>函数不同，调用select()函数之后，select() 函数会清空它所检测的socket描述符
		>集合，导致每次调用select()之前都必须把socket描述符重新加入到待检测的集合中；
		>因此，select()函数适合于只检测一个socket描述符的情况，而poll()函数适合于
		>大量socket描述符的情况；
	nfds：	
		>nfds_t类型的参数，用于标记数组fds中的结构体元素的总数量；
	timeout：	
		>是poll函数调用阻塞的时间，单位：毫秒；
返回值:
	>0：
		>数组fds中准备好读、写或出错状态的那些socket描述符的总数量；
	==0：
		>数组fds中没有任何socket描述符准备好读、写，或出错；此时poll超时，超时时间
		>是timeout毫秒；换句话说，如果所检测的socket描述符上没有任何事件发生的话，
		>那么poll()函数会阻塞timeout所指定的毫秒时间长度之后返回，如果timeout==0，
		>那么 poll() 函数立即返回而不阻塞，如果timeout==INFTIM，那么poll() 函数会
		>一直阻塞下去，直到所检测的socket描述符上的感兴趣的事件发生时才返回，如果
		>感兴趣的事件永远不发生，那么poll()就会永远阻塞下去；
	-1：  
		>poll函数调用失败，同时会自动设置全局变量errno；
#endif
void Eventfd::start()//运行在线程B
{
	_isStarted=true;

	//创建pollfd结构体
	struct pollfd pfd;
	//设置监控描述符为_fd
	pfd.fd=_fd;	//_fd为eventfd
	//设置监控的事件为可读事件
	pfd.events=POLLIN;

	while(_isStarted)
	{
		//获得已经就绪的描述符数量
		int nready=::poll(&pfd,1,5000);//该结构体数组只有一个元素，等待5000ms
		if(nready==-1 && errno==EINTR){
			//产生原因：被信号打断
			continue;
		}else if(nready==-1){
			//poll函数调用失败
			return;
		}else if(nready==0){
			//超时
			printf(">> poll timeout!\n");
		}else{
			//获得了已就绪的描述符
			if(pfd.revents & POLLIN){
				//判断该描述符是否是处于可读状态
				handlRead();//执行读操作，获得计数器counter的值
				if(_cb){//表示有回调函数
					//执行回调函数
					_cb();
				}
			}
		}
	}
}

//停止函数
void Eventfd::stop()
{
	if(_isStarted){
		_isStarted=false;
	}
}


//头文件：
//	#include <sys/eventfd.h>
//函数原型：
//	int eventfd(unsigned int initval, int flags);
//主要数据结构：
//	struct eventfd_ctx {
//		struct kref kref;
//		wait_queue_head_t wqh;
//		__u64 count;
//		unsigned int flags;
//	};
//
//说明：
//	>eventfd系统调用创建一个匿名文件，关联一个eventfd_ctx的结构体，
//	>里面的count用来计数，wqh用来唤醒等待eventfd事件的task。看来
//	>只能在父子进程中做简单的消息通知，性能上比pipe好一些。
//	>eventfd()创建一个“eventfd对象”，这个对象能被用户空间应用用作
//	>一个事件等待/响应机制，靠内核去响应用户空间应用事件。
//参数；
//initval:
//	>这个对象包含一个由内核保持的无符号64位整型计数器。这个计数器
//	>由参数initval说明的值来初始化。
//flags:
//	>它的标记可以有以下属性：
//	>EFD_CLOECEX，EFD_NONBLOCK，EFD_SEMAPHORE
//	>在linux直到版本2.6.26，这个flags参数是没用的，必须指定为0。
//返回值：
//	>它返回了一个引用eventfd object的描述符。这个描述符可以支持以下操作：
//	>read：
//		>如果计数值counter的值不为0，读取成功，获得到该值。如果counter的值为0，
//		>非阻塞模式，会直接返回失败，并把errno的值置为EINVAL。如果为阻塞模式，
//		一直会阻塞到counter为非0位置。
//	>write：
//		>会增加8字节的整数在计数器counter上，如果counter的值达到0xfffffffffffffffe时
//		>，就会阻塞。直到counter的值被read。阻塞和非阻塞情况同上面read一样。
//	>close：
//		>这个操作不用说了。

//在计数器counter上增加8字节的整数
int Eventfd::wakeup()//运行在线程A
{
	uint64_t one=1;
	//向计数器增加数字
	int ret=::write(_fd,&one,sizeof(one));
	if(ret!=sizeof(one)){
		perror(">> write");
	}
}

int Eventfd::createEventfd()
{
	//8字节的计数器初始化为10
	int fd=::eventfd(10,0);
	if(fd==-1){
		perror(">>eventfd");
	}
	return fd;
}

void Eventfd::handleRead()
{
	//用来存储计数器counter的值
	uint64_t howmany;
	int ret=::read(_fd,&howmany,sizeof(uint64_t));
	if(ret!=sizeof(howmany)){
		perror(">> read");
	}
}
}//end of namespace wd
