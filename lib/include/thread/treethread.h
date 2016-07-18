
#ifndef TREE_THREAD_H
#define TREE_THREAD_H

#include "basethread.h"
#include "threadmanager.h"

class TreeThread : public BaseThread
{
public:
	TreeThread(void *arg, char exit = ThreadManager::EXIT_NORMAL);
	virtual ~TreeThread();

	int		Register(BaseThread *bt, char exit = ThreadManager::EXIT_NORMAL);
	void	Exit();
	void	Wait();
protected:
	ThreadManager	*m_manager;
};

#endif
