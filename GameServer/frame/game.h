
#ifndef GAME_FRAME_H
#define GAME_FRAME_H

#include "define.h"
#include "messagehandler.h"
#include "common/datastructure/gamehash.h"
#include "lib/include/frame/frame.h"

class Game : public Frame
{
public:

    ~Game();

    static Game &Instance()
    {
        static Game frame;
        return frame;
    }

    static const unsigned char MAX_DB_THREAD = 2;

    bool	Init();    //初始化

	void	Update(unsigned int interval, time_t now);  //更新
    void	Exit();
	void	Wait();

	bool	Start();
	bool	Cmd(char *buf);

	ThreadID 	GetThreadID();
	inline bool HandleMessage(Role *role, NetMsg *msg){return m_message_handler.HandleMessage(role, msg);}
public:
	ThreadID		m_global_id;
	ThreadID		m_db_id[2];
	ThreadID 		m_cur_thread_id;
	ThreadID		m_log_id;
	NetHandle		m_database_server_handle;
	SOCKET			m_gateway_server_net_id;
private:
	Game();
	MessageHandler 	m_message_handler;
};

#endif // FRAME_H
