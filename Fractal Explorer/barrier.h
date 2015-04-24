#ifndef BARRIER_H
#define BARRIER_H

#include "globals.h"



class barrier
{
public:
	barrier();
	void wait();
private:
	mutex waitCheck;
	condition_variable barrierLock;
	int threadWaitCount;
	int totalThreads;
	const int waitTime = 5;
};

#endif