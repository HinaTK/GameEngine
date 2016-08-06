
#ifndef GATE_LISTENER_H
#define GATE_LISTENER_H

#include "lib/include/frame/listener.h"
#include "lib/include/frame/bufmanager.h"
#include "lib/include/common/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/

class GateListener : public Listener
{
public:
	GateListener(SocketThread *t, int size = 0);
	virtual ~GateListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);

	int				buf_size;
protected:
	virtual bool	RecvBuf();
	
	RecvBuffer	m_recv_buf;
};

#endif