
#ifndef GATE_LISTENER_H
#define GATE_LISTENER_H

#include "lib/include/frame/bufmanager.h"
#include "lib/include/frame/listener.h"
/*
	监听者，监听所有数据的读写状态
*/

class GateListener : public Listener
{
public:
	GateListener(SocketThread *t, int size = 0);
	virtual ~GateListener();

	typedef void (GateListener::*RecvFunc)(unsigned int len, char *buf);

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void		SetMsgID(unsigned int id){m_msg_id = id;}
	void		Send(const char *buf, unsigned int len);
	//void		Recv(NetHandle handle, unsigned int len, char *buf);

	void		Bind(unsigned int len, char *buf);
	void		Dispatch(unsigned int len, char *buf);
	RecvFunc	Recv;

	bool		IsHandshake(){ return m_is_handshake; }
protected:
	virtual bool	RecvBuf();
	RecvBuffer		m_recv_buf;
	unsigned int 	m_msg_id;
	bool			m_is_handshake;
	time_t			m_build_time;
};

#endif