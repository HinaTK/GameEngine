
#ifndef GATE_CREATOR_H
#define GATE_CREATOR_H

#include "gatebuffer.h"
#include "lib/include/frame/listener.h"
/*
	* 完成握手（防止syn攻击）
	* 创建角色
*/

class GateCreator : public Listener
{
public:
	GateCreator(SocketThread *t, int size = 0);

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void		Send(const char *buf, unsigned int len);
	void		Recv(NetHandle handle, unsigned int len, char *buf);

protected:
	virtual bool	RecvBuf();
	
	GateBuffer	m_recv_buf;
};

#endif