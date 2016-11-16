
#ifndef GATE_HANDSHAKE_H
#define GATE_HANDSHAKE_H

#include "lib/include/frame/nethandler.h"
#include "lib/include/frame/bufmanager.h"

/*
	接收者，管理所有的请求链接
	注：不作对象池管理，因为个数少且不会频繁分配与释放内存
*/

class GateHandshake : public NetHandler
{
public:
	GateHandshake(SocketThread *t, int size = 0);
    virtual ~GateHandshake(){}

	virtual void	OnCanRead();

protected:
	bool		RecvBuf();
	void		Handshake(unsigned int len, char *buf);
private:
	RecvBuffer		m_recv_buf;
};

#endif
