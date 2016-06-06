
#ifndef BASE_LISTENER_H
#define BASE_LISTENER_H

#include "listener.h"
#include "bufmanager.h"
#include "lib/include/common/mutex.h"
/*
	监听者，监听所有数据的读写状态
*/

class BaseListener : public Listener
{
public:
	BaseListener(SocketThread *t, int size = 0);
	virtual ~BaseListener(){}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual bool	RecvBuf();
	virtual bool	AnalyzeBuf();
	int			buf_size;
	TestBuffer	m_recv_buf;
};

#endif