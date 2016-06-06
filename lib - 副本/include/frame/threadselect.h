
#ifndef THREAD_SELECT_H
#define THREAD_SELECT_H

#include "threadnet.h"

class NetManager;
class ThreadManager;
class SocketThread : public ThreadNet
{
public:
	virtual ~SocketThread();
	SocketThread(ThreadManager *manager, NetManager *net_manager);

	void			SetCanWrite(NetHandler *handler);
	void			SetCanNotWrite(NetHandler *handler);

protected:
	bool			Run();
	
	void			ClearHandler();
	void			InitNetHandler(NetHandler *handler);
private:
	
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
	fd_set			m_tmp_read_set;
	fd_set			m_tmp_write_set;
	struct timeval	m_tv;
};


#endif // !SOCKET_THREAD_H
