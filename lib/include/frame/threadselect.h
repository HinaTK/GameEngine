
#ifndef THREAD_SELECT_H
#define THREAD_SELECT_H

#include "threadnet.h"

class NetManager;
class SocketThread : public ThreadNet
{
public:
	virtual ~SocketThread();
	SocketThread(ThreadManager *manager, void *arg);

	void			SetCanWrite(NetHandler *handler);
	void			SetCanNotWrite(NetHandler *handler);

protected:
	bool			Run();
	
	void			ClearHandler();
	void			InitNetHandler(NetHandler *handler);
private:
	NetManager		*m_net_manager;
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
	fd_set			m_tmp_read_set;
	fd_set			m_tmp_write_set;
	struct timeval	m_tv;
};


#endif // !SOCKET_THREAD_H
