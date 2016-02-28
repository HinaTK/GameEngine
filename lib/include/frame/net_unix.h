
#ifndef NET_UNIX_H
#define NET_UNIX_H

#include "net_base.h"

class NetUnix : public NetBase
{
public:
    virtual ~NetUnix();
    NetUnix();

    virtual void	Loop();
    virtual void	InitNetHandler(NetHandler *handler);
    virtual void	ReplaceHandler();		// 将该句柄的控制者替换（用于将握手者-->监听者）
    virtual void	ClearHandler();
    virtual void	SetCanWrite(SOCKET sock);
    virtual void	SetCanNotWrite(SOCKET sock);

    SOCKET			GetEpollFD(){return m_epoll_fd;}
protected:
    SOCKET			m_epoll_fd;

};

#endif
