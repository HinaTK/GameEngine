
#ifndef THREAD_H
#define THREAD_H

#ifdef __unix
#include <pthread.h>
#endif

class Thread
{
public:
	Thread(){}
	~Thread(){}

    bool Create(void * func(void *), void *arg = NULL);

	bool Join();
private:

#ifdef __unix
	pthread_t m_thread;
#endif
#ifdef WIN32
	// 由于windows.h 与 winsock2.h的包含问题，用void * 代替HANDLE
	//HANDLE m_thread;
	void * m_thread;
#endif

};

#endif
