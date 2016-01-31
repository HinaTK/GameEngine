
#ifndef GUIMI_H
#define GUIMI_H

#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/frame/netmanager.h"
#include "lib/include/timemanager/timemanager.h"
#include "lua/interface.h"
#include "scene/scenemanager.h"

class NewFrame : public Frame
{
public:

	~NewFrame();

	static NewFrame &Instance()
	{
		static NewFrame frame;
		return frame;
	}

	bool	Init(const char *config);    //初始化

	void	Update(unsigned int interval, time_t now);  //更新
	void	Loop();
	virtual bool Run();
	void	Exit();
	void	Wait();
	void	OuterRecv(GameMsg *msg);
	void	InnerRecv(GameMsg *msg);

	void	PushMsg(GameMsg *msg, SceneID scene_id = 0);

	Interface *GetInterface(){ return &m_lua_interface; }
	SceneManager *GetSceneManager(){ return &m_scene_manager; }
	NetManager *GetNetManager(){ return &m_net_manager; }
	void	ChangeServer();

public:

	NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;
private:
	NewFrame();
	TimeEventManager	m_time_event_manager;
	NetManager			m_net_manager;

	typedef game::Hash<NetHandle, int> NET_HANDLE_THREAD_HASH;
	NET_HANDLE_THREAD_HASH m_net_handle_thread_hash;

	Interface			m_lua_interface;
	SceneManager		m_scene_manager;

};

#endif // FRAME_H
