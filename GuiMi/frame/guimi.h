
#ifndef GUIMI_H
#define GUIMI_H

#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/timemanager/timemanager.h"
#include "lib/include/script/luaengine.h"
#include "callback.h"

class NewFrame : public Frame
{
public:

	static const UInt32 UPDATE_INTERNAL = 80;		// ��λ���룬ÿ��80�������һ��
	static const UInt32 SendSleepTime = 50;			// ��λ���룬��������Ϣ����Ϊ��ʱ��˯��50����
	static const UInt32 RecvSleepTime = 50;			// ��λ���룬��������Ϣ����Ϊ�պ�û�е�����ʱ�䣬˯��50����

	~NewFrame();

	static NewFrame &Instance()
	{
		static NewFrame frame;
		return frame;
	}

	bool	InitConfig();

	bool	Init();    //��ʼ��

	void	Update(unsigned int interval, time_t now);  //����
	virtual bool Run();
	void	Exit();
	void	Wait();
	void	OuterRecv(GameMsg *msg);
	void	InnerRecv(GameMsg *msg);

	void	PushMsg(GameMsg *msg, SceneID scene_id = 0);

	void	ChangeServer();

public:

	NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;
private:
	NewFrame();

	OuterCallBack		m_o_call_back;
	InnerCallBack		m_i_call_back;

	TimeEventManager	m_time_event_manager;

	typedef game::Hash<NetHandle, int> NET_HANDLE_THREAD_HASH;
	NET_HANDLE_THREAD_HASH m_net_handle_thread_hash;

	LuaEngine			m_lua_engine;

};

#endif // FRAME_H
