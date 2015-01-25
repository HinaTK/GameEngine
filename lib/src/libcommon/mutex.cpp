
#include "mutex.h"

Mutex::Mutex()
{
#ifdef WIN32
	InitializeCriticalSection(&m_mutex);
#endif
#ifdef __unix
	pthread_mutex_init(&m_mutex, NULL);
#endif // __unix
}

Mutex::~Mutex()
{
#ifdef WIN32
	DeleteCriticalSection(&m_mutex);
#endif
	
#ifdef __unix
	pthread_mutex_destroy(&m_mutex);
#endif // __unix
}

void Mutex::Lock()
{
#ifdef WIN32
	EnterCriticalSection(&m_mutex);
#endif
#ifdef __unix
	pthread_mutex_lock(&m_mutex);
#endif // __unix
}

void Mutex::Unlock()
{
#ifdef WIN32
	LeaveCriticalSection(&m_mutex);
#endif
#ifdef __unix
	pthread_mutex_unlock(&m_mutex);
#endif // __unix
}


