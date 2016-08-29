
#ifndef ROLE_H
#define ROLE_H

#include "obj.h"
#include "common/socketdef.h"
#include "common/datastructure/msgqueue.h"

class Role:public Obj
{
public:
	Role();
	~Role();

	
private:
	ThreadID	m_net_id;	// game 的网络线程地址
	NetHandle	m_handle;	// gate 的网络句柄
	MsgQueue 	m_msg_queue;
};

#endif