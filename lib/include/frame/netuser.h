
#ifndef NET_USER_H
#define NET_USER_H

#include "bufmanager.h"
#include "common/systemdef.h"


class NetUser
{
public:
	~NetUser(){};
	NetUser(SOCKET sock) :m_sock(sock)
	{};

	/* 
		��Ҫʹ��BufManager	&GetBufManager(){ return m_buf_manager; }
		��Ϊ������ʹ��ʱ,BufManager manager = GetBufManager();����ǰ����
	*/
	BufManager	*GetBufManager(){ return &m_buf_manager; }		

	SOCKET		GetSocket(){ return m_sock; }

	void *		operator new(size_t c);
	void		operator delete(void *m);

private:
	BufManager	m_buf_manager;
	SOCKET		m_sock;
};


#endif