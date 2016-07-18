
#include "treethread.h"

TreeThread::TreeThread(void *arg, char exit /*= ThreadManager::EXIT_NORMAL*/)
: BaseThread(arg, exit)
, m_manager(new ThreadManager())
{

}

TreeThread::~TreeThread()
{
	if (m_manager != NULL)
	{
		delete m_manager;
		m_manager = NULL;
	}
}

int TreeThread::Register(BaseThread *bt, char exit /*= ThreadManager::EXIT_NORMAL*/)
{
	return m_manager->Register(bt, exit);
}

void TreeThread::Exit()
{
	m_manager->Exit();
	BaseThread::Exit();
}

void TreeThread::Wait()
{
	m_manager->Wait();
	BaseThread::Wait();
}