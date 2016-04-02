
#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include "nethandler.h"
#include "common/datastructure/gamearray.h"
#include "common/datastructure/msgqueue.h"
#include "lib/include/thread/basethread.h"

class ThreadManager;
class NetManager;
class SocketThread : public BaseThread
{
	virtual ~SocketThread(){}
	SocketThread(ThreadManager *manager);

	struct RemoveInfo
	{
		NetHandle handle;
		int reason;
	};

protected:
	void	Init(void *arg);
	bool	Run();
	void	RecvMsg(short type, unsigned char sid, int len, const char *data);

	void	ClearHandler();

private:
	NetManager		*m_net_manager;
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
	fd_set			m_tmp_read_set;
	fd_set			m_tmp_write_set;
	struct timeval	m_tv;

	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	typedef game::Vector<RemoveInfo>	INVALID_HANDLE;

	NET_HANDLER_ARRAY		m_net_handler;
	INVALID_HANDLE			m_invalid_handle;
};


#endif // !SOCKET_THREAD_H
