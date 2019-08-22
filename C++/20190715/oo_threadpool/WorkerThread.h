#pragma once

#include "Thread.h"

namespace wd
{

class Threadpool;
class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool &threadpool);
	~WorkerThread();

	void run();
private:
	//数据成员
	Threadpool &_threadpool;
};
}//end of namespace wd
