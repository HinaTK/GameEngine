
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include "common/datastructure/msgqueue.h"
/*
	Ŀ�ģ��Զ��̲߳��д������̲���
*/

class GameMsg;
class GameThread
{
public:
	GameThread(int index);
	~GameThread();

	void	Update();

	void	Run();

	void	PushMsg(GameMsg *msg);

	void	Recv(GameMsg *msg);
	// �ȴ��߳�ִ�����
	void	Wait();

	int		GetIndex(){ return m_index; }
private:
	std::thread		*m_thread;
	int				m_index;	// �߳�����
	bool			m_is_exit;

	
	MsgQueue<GameMsg *> m_msg_queue;
};

#endif // !GAME_THREAD_H
