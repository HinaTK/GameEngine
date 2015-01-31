
#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <map>
//#include "frame.h"
#include "netuser.h"
#include "nethandler.h"
#include "common/systemdef.h"
#include "common/datastructure/gamevector.h"
#include "common/datastructure/gamearray.h"

class NetManager
{
public:
	~NetManager();
	NetManager();
	
	bool			InitServer(char *ip, unsigned short port, int backlog, NetID &net_id, bool is_web = false);
	bool			ConnectServer(char *ip, unsigned short port, NetID &net_id);

	void			Listen();

	NetHandle		AddNetHandler(NetHandler *handler);			
	void			RemoveHandler(NetHandle handle);
	void			ReplaceHandler(NetHandler *handler);		// 将该句柄的控制者替换（用于将握手者-->监听者）
	void			ClearHandler();
	
	MsgQueue		*GetMsgQueue(){ return &m_queue; }

	void			Send(NetHandle handle, const char *buf, unsigned int length);

public:
	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	NET_HANDLER_ARRAY		m_net_handler;
protected:
	typedef game::Vector<NetHandle> INVALID_HANDLE;

	MsgQueue		m_queue;
	INVALID_HANDLE	m_invalid_handle;

#ifdef WIN32
public:

	NetID			GetSocketInfo(fd_set &read_set, fd_set &write_set);
	fd_set			*GetWriteSet(){ return &m_write_set; }

protected:
	NetID			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
#endif

#ifdef __unix
public:
	NetID			GetEpollFD(){return m_epoll_fd;}
protected:
	NetID			m_epoll_fd;
#endif

};

#endif