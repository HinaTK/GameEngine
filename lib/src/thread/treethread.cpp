
#include "treethread.h"

TreeThread::TreeThread(ThreadManager *manager, void *arg, char exit /*= ThreadManager::EXIT_NORMAL*/)
: BaseThread(manager, exit)
, m_sub_manager(new ThreadManager())
{

}

TreeThread::~TreeThread()
{
	if (m_sub_manager != NULL)
	{
		delete m_sub_manager;
		m_sub_manager = NULL;
	}
}

int TreeThread::Register(BaseThread *bt, char exit /*= ThreadManager::EXIT_NORMAL*/)
{
	return m_sub_manager->Register(bt, exit);
}

void TreeThread::Exit()
{
	m_sub_manager->Exit();
	BaseThread::Exit();
}

void TreeThread::Wait()
{
	m_sub_manager->Wait();
	BaseThread::Wait();
}