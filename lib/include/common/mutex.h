
#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <mutex>

#ifdef WIN32
#include <windows.h>
#endif
#ifdef __unix
#include <pthread.h>
#endif // __unix


class Mutex
{
public:
	Mutex();
	~Mutex();

	void Lock();

	void Unlock();

private:
	Mutex(const Mutex&);
	void operator=(const Mutex&);

#ifdef WIN32
	CRITICAL_SECTION m_mutex;
#endif // WIN32

#ifdef __unix
	pthread_mutex_t m_mutex;
#endif // __unix	
};


class MutexLock
{
public:
	explicit MutexLock(Mutex *mutex) :m_mutex(mutex)
	{
		m_mutex->Lock();
	};
	~MutexLock()
	{ 
		m_mutex->Unlock(); 
	};

private:
	// ≤ª‘ –Ì∏¥÷∆
	MutexLock(const MutexLock&);
	void operator=(const MutexLock&);

	Mutex *m_mutex;
};

#define LOCK(mutex)\
	mutex.lock(); \
{

#define UNLOCK(mutex)\
}\
	mutex.unlock();

#endif // !MUTEX_LOCK_H
