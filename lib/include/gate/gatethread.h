
#ifndef GATE_THREAD_H
#define GATE_THREAD_H

#include "lib/include/frame/socketthread.h"
#include "common/datastructure/gamehash.h"
#include "common/datastructure/msgqueue.h"
#include "common/datastructure/gamearray.h"

class ThreadManager;
class GateThread : public SocketThread
{
public:
	virtual ~GateThread(){}
	GateThread(ThreadManager *manager, int index, ThreadID global);

	void	Dispatch(unsigned int msg_id, NetMsg &msg);


protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	NetHandle		m_cneter_handle;
	int				m_index;
	/*
		新建立的role在这里注册一个消息队列，将索引设置给listener
	*/
	typedef game::Array<MsgQueue<NetMsg> * > ROLE_MSG;
	ROLE_MSG		m_role_msg;
	ThreadID		m_global;
};

namespace New
{
	EXPORT GateThread * _GateThread(ThreadManager *manager, int index, ThreadID id);
}
#endif