
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
	Role(MsgQueue<NetMsg> *queue, unsigned int index, ThreadID gate_id, NetHandle handle);
	~Role();

	bool	Init(SceneManager *manager);

	void	Send(int len, char *data);
private:
	SceneManager		*m_manager;
	
	MsgQueue<NetMsg> 	*m_msg_queue;
	unsigned int		m_msg_index;
	ThreadID			m_gate_id;	// gate 的网络线程地址
	NetHandle			m_handle;	// gate 的网络句柄
};

#endif