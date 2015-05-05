
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
		不要使用BufManager	&GetBufManager(){ return m_buf_manager; }
		因为当这样使用时,BufManager manager = GetBufManager();会提前析构
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