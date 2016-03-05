
#ifndef NET_UNIX_H
#define NET_UNIX_H

#include "net_base.h"

class NetManager : public NetBase
{
public:
    virtual ~NetManager();
    NetManager();

    virtual void	Loop();
    virtual void	InitNetHandler(NetHandler *handler);
    virtual void	ReplaceHandler();		// 将该句柄的控制者替换（用于将握手者-->监听者）
    virtual void	ClearHandler();
    virtual void	SetCanWrite(NetHandler *handler);
    virtual void	SetCanNotWrite(NetHandler *handler);

    SOCKET			GetEpollFD(){return m_epoll_fd;}
protected:
    SOCKET			m_epoll_fd;

};

#endif
