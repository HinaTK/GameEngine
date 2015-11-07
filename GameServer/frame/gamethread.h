
#ifndef GAME_THREAD_H
#define GAME_THREAD_H

#include <thread>
#include "common/datastructure/msgqueue.h"
/*
	目的：以多线程并行代替多进程并行
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
	// 等待线程执行完毕
	void	Wait();

	int		GetIndex(){ return m_index; }
private:
	std::thread		*m_thread;
	int				m_index;	// 线程索引
	bool			m_is_exit;

	
	MsgQueue<GameMsg *> m_msg_queue;
};

#endif // !GAME_THREAD_H
