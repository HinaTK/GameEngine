
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"
#include "netproto.h"
#include "lib/include/frame/message.h"
#include "common/serverdef.h"
#include "common/datastructure/msgqueue.h"


class SceneManager;
class Role:public Obj
{
public:
	Role(MsgQueue<NetMsg> *queue, unsigned int index, ThreadID gate_id, NetHandle handle);
	~Role();

	bool	Init(SceneManager *manager);
	void 	Dispatch();
	void	Send(int len, char *data);

	void	Logout();

	RoleID	GetID(){return m_id;}
private:
	SceneManager		*m_manager;
	
	MsgQueue<NetMsg> 	*m_msg_queue;
	unsigned int		m_msg_index;
	ThreadID			m_gate_id;	// gate 的网络线程地址
	NetHandle			m_handle;	// gate 的网络句柄

private:
	RoleID				m_id;
protected:
	struct HandlerItem 
	{
		HandlerItem():func(0), length(0){}
		HandlerItem(HandleFunc f, int s):func(f), length(s){}
		HandleFunc		func;
		unsigned short	length;
	};
	HandlerItem m_function_list[Proto::GAME_END];

	void 	Register();
	void	CSLogin(NetMsg *msg);
};

#endif