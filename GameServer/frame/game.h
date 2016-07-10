
#ifndef GAME_FRAME_H
#define GAME_FRAME_H

#include "define.h"
#include "common/socketdef.h"
#include "common/datastructure/gamehash.h"
#include "lib/include/frame/frame.h"

class NewFrame : public Frame
{
public:

    ~NewFrame();

    static NewFrame &Instance()
    {
        static NewFrame frame;
        return frame;
    }

    bool	Init();    //初始化

	void	Update(unsigned int interval, time_t now);  //更新
    void	Exit();
	void	Wait();

	void	Start();
public:

	NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;
private:
	NewFrame();

	typedef game::Hash<NetHandle, int> NET_HANDLE_THREAD_HASH;
	NET_HANDLE_THREAD_HASH m_net_handle_thread_hash;
	
};

#endif // FRAME_H
