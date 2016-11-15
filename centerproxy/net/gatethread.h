
#ifndef GATE_THREAD_H
#define GATE_THREAD_H

#include <queue>
#include "lib/include/frame/socketthread.h"
#include "lib/include/common/serverconfig.h"
#include "common/datastructure/gamehash.h"
#include "common/datastructure/msgqueue.h"
#include "common/datastructure/gamearray.h"

class ThreadManager;
class GateCreator;
class TimerQueue;
class GateThread : public SocketThread
{
public:
	virtual ~GateThread();
	GateThread(ThreadManager *manager, unsigned char index, ThreadID login_id, TPT proto_type);

	void	Dispatch(unsigned int msg_id, NetHandle handle, unsigned short len, char *data);
	void	Dispatch(unsigned int msg_id, NetMsg &msg);
	void	PushTimer(NetHandle handle);
	void 	RegRole(NetHandle handle);
	void	DelRole(unsigned int index);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
	bool	DoSomething();
private:
	typedef game::Array<MsgQueue<NetMsg> *> ROLE_MSG;
	ROLE_MSG		m_role_msg;

	NetHandle		m_center_handle;
	TimerQueue		*m_timer_queue;
	unsigned char	m_index;
	ThreadID		m_login_id;
	TPT				m_proto_type;
};

#endif