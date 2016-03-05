
#ifndef WIN_NET_H
#define WIN_NET_H

#include "net_base.h"

class NetManager : public NetBase
{
public:
	virtual ~NetManager();
	NetManager();
	
	virtual void	Loop();
	virtual void	SetCanWrite(NetHandler *handler);
	virtual void	SetCanNotWrite(NetHandler *handler);

	SOCKET			GetSocketInfo(fd_set &read_set, fd_set &write_set);
	fd_set			*GetWriteSet(){ return &m_write_set; }
	fd_set			*GetReadSet(){ return &m_read_set; }

protected:
	virtual void	InitNetHandler(NetHandler *handler);
	virtual void	ReplaceHandler();		// 将该句柄的控制者替换（用于将握手者-->监听者）
	virtual void	ClearHandler();
protected:
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;

};

#endif