
#ifndef GATE_THREAD_H
#define GATE_THREAD_H

#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamehash.h"
#include "common/datastructure/msgqueue.h"

class ThreadManager;
class GateThread : public SocketThread
{
public:
	virtual ~GateThread(){}
	GateThread(ThreadManager *manager, int index);

	void	Dispatch(NetMsg *msg);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	NetHandle		m_cneter_handle;
	int				m_index;
	typedef game::Hash<NetHandle, MsgQueue<NetMsg> * > ROLE_MSG;
	ROLE_MSG		m_role_msg;
};

namespace New
{
	EXPORT GateThread * _GateThread(ThreadManager *manager, int index);
}
#endif