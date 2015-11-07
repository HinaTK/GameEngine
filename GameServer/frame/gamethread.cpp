
#include "gamethread.h"
#include "lib/include/common/mutex.h"

void *Update(void * arg)
{
	GameThread *gt = (GameThread *)arg;
	gt->Update();
	return NULL;
}

GameThread::GameThread(int index)
: m_thread(NULL)
, m_index(index)
, m_is_exit(false)
{

}

GameThread::~GameThread()
{

}


void GameThread::Update()
{
	for (int i = 0; i < 50; ++i)
	{
		printf("index:%d : %d\n", m_index, i);
	}
}

void GameThread::Run()
{
	m_thread = new std::thread(::Update, this);
}

void GameThread::PushMsg(GameMsg *msg)
{
	m_msg_queue.Push(msg);
}

void GameThread::Recv(GameMsg *msg)
{
	
}

void GameThread::Wait()
{
	if (m_thread)
	{
		m_thread->join();
	}
}

