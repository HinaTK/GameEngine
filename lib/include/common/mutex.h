
#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <mutex>

class MutexLock
{
public:
	explicit MutexLock(std::mutex *mutex) :m_mutex(mutex)
	{
		m_mutex->lock();
	};
	~MutexLock()
	{ 
		m_mutex->unlock(); 
	};

private:
	// ≤ª‘ –Ì∏¥÷∆
	MutexLock(const MutexLock&);
	void operator=(const MutexLock&);

	std::mutex *m_mutex;
};

#define LOCK(mutex)\
	mutex.lock(); \
{

#define UNLOCK(mutex)\
}\
	mutex.unlock();

#endif // !MUTEX_LOCK_H
