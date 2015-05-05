
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
	
	bool			InitServer(char *ip, unsigned short port, int backlog, SOCKET &net_id, bool is_web = false);
	bool			ConnectServer(char *ip, unsigned short port, SOCKET &net_id);

	void			Listen();
	void			Send(NetHandle handle, const char *buf, unsigned int length);

	NetHandle		AddNetHandler(NetHandler *handler);			
	void			RemoveHandler(NetHandle handle);
	void			AddReplaceHandler(NetHandler *handler);

	void			ReplaceHandler();		// 将该句柄的控制者替换（用于将握手者-->监听者）
	void			ClearHandler();
	
	MsgQueue		*GetMsgQueue(){ return &m_queue; }
	void			Exit(){ m_is_run = false; }

public:
	typedef game::Array<NetHandler*>	NET_HANDLER_ARRAY;
	NET_HANDLER_ARRAY		m_net_handler;
protected:
	typedef game::Vector<NetHandle>		INVALID_HANDLE;
	typedef game::Vector<NetHandler*>	REPLACE_HANDLER;

	MsgQueue			m_queue;
	INVALID_HANDLE		m_invalid_handle;
	REPLACE_HANDLER		m_replace_handler;
	bool				m_is_run;

#ifdef WIN32
public:

	SOCKET			GetSocketInfo(fd_set &read_set, fd_set &write_set);
	fd_set			*GetWriteSet(){ return &m_write_set; }
	fd_set			*GetReadSet(){ return &m_read_set; }

protected:
	SOCKET			m_max_fd;
	fd_set			m_read_set;
	fd_set			m_write_set;
#endif

#ifdef __unix
public:
	SOCKET			GetEpollFD(){return m_epoll_fd;}
protected:
	SOCKET			m_epoll_fd;
#endif

};

#endif