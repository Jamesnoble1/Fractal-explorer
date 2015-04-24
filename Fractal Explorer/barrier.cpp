#include "barrier.h"
#include <iostream>
barrier::barrier()
{
	threadWaitCount = 0;
	totalThreads = 0;
}

void barrier::wait()
{
	
	
	unique_lock<mutex> lock(waitCheck);
	threadWaitCount++;
	if (threadWaitCount == MAX_THREADS+1 )
	{
		threadWaitCount = totalThreads;
		barrierLock.notify_all();
		//wait to make sure all threads unlock 
		sleep_for(milliseconds(waitTime));
		
	}
	else
	{
		barrierLock.wait(lock, [this]{return threadWaitCount == 0; }); //lamda to test if wait count is correct to prevent spurious wake ups	
	}
}