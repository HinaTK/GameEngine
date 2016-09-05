
#ifndef FILTER_THREAD_H
#define FILTER_THREAD_H

#include "lib/include/thread/basethread.h"

class ThreadManager;
class FilterThread : public basethread
{
public:
	FilterThread(ThreadManager *manager);


};

#endif

