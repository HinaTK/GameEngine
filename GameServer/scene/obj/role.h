
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"
#include "lib/include/frame/message.h"
#include "common/serverdef.h"
#include "common/datastructure/msgqueue.h"


class SceneManager;
class Role:public Obj
{
public:
	Role(SceneManager *manager, ThreadID gate_id, NetHandle handle);
	~Role();

	void	Send(int len, char *data);
private:
	SceneManager	*m_manager;
	ThreadID		m_gate_id;	// gate 的网络线程地址
	NetHandle		m_handle;	// gate 的网络句柄
	MsgQueue<NetMsg> 	m_msg_queue;
};

#endif