
#ifndef NET_THREAD_H
#define NET_THREAD_H

#include <vector>
#include "common/proto.h"
#include "lib/include/gate/gatethread.h"


class ThreadManager;
class NetThread : public GateThread
{
public:
	virtual ~NetThread();
	NetThread(ThreadManager *manager, int index);

	void	Dispatch(unsigned int msg_id, NetMsg &msg);
	unsigned int RegRole(NetHandle handle);
	void		DelRole(unsigned int index);
	void		ChangeChannel(NetHandle handle);

	void	Recv(NetMsg *msg){ };

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	typedef game::Array<MsgQueue<NetMsg> *> ROLE_MSG;

	ThreadID 		m_cur_thread_id;
	int			m_index;
	NetHandle	m_cneter_handle;
	ROLE_MSG		m_role_msg;
};

#endif