
#ifndef GUIMI_H
#define GUIMI_H

#include "common/commonvariable.h"
#include "common/datastructure/gamehash.h"
#include "lib/include/common/thread.h"
#include "lib/include/frame/frame.h"
#include "lib/include/timemanager/timemanager.h"
#include "lua/interface.h"

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

	bool	Init(const char *config);    //��ʼ��

	void	Update(unsigned int interval, time_t now);  //����
	virtual bool Run();
	void	Exit();
	void	Wait();
	void	OuterRecv(GameMsg *msg);
	void	InnerRecv(GameMsg *msg);

	void	PushMsg(GameMsg *msg, SceneID scene_id = 0);

	Interface *GetInterface(){ return &m_lua_interface; }
	void	ChangeServer();

public:

	NetHandle	m_database_server_handle;
	SOCKET		m_gateway_server_net_id;
private:
	NewFrame();


	TimeEventManager	m_time_event_manager;

	typedef game::Hash<NetHandle, int> NET_HANDLE_THREAD_HASH;
	NET_HANDLE_THREAD_HASH m_net_handle_thread_hash;

	Interface			m_lua_interface;

};

#endif // FRAME_H
