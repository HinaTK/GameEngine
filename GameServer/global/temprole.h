
#ifndef GLOBAL_TEMP_ROLE_H
#define GLOBAL_TEMP_ROLE_H

#include "lib/include/common/message.h"
#include "common/datastructure/msgqueue.h"

class Global;
class TempRole
{
public:
	TempRole(){}
	TempRole(MsgQueue<NetMsg> *queue, unsigned int index, ThreadID gate_id, NetHandle handle);

	void 	Dispatch(Global *global);
	void	Logout();
private:
	
	MsgQueue<NetMsg> 	*m_msg_queue;
	unsigned int		m_msg_index;
	ThreadID			m_gate_id;	// gate 的网络线程地址
	NetHandle			m_handle;	// gate 的网络句柄
};

#endif