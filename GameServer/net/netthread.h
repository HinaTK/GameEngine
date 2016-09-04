
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

	
	void	Recv(NetMsg *msg){ };

	// 接收其它进程数据
	void	InnerRecv(NetMsg *msg);

protected:
	bool	Init();
	void	Ready();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:
	
	ThreadID 		m_cur_thread_id;
	int			m_index;
	NetHandle	m_cneter_handle;

};

#endif