
#ifndef THREAD_SELECT_H
#define THREAD_SELECT_H

#include "threadnet.h"

class NetManager;
class ThreadManager;
class SocketThread : public ThreadNet
{
public:
	virtual ~SocketThread();
	SocketThread(ThreadManager *manager);

	void			SetCanWrite(NetHandler *handler);
	void			SetCanNotWrite(NetHandler *handler);

protected:
	bool			Run() final;
	bool			CMD(short type, ThreadID sid, int len, const char *data);
	void			InitNetHandler(NetHandler *handler);
	void			ClearHandler();
private:
	
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
	fd_set			m_tmp_read_set;
	fd_set			m_tmp_write_set;
	struct timeval	m_tv;
};


#endif // !SOCKET_THREAD_H
