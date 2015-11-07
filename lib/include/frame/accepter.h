
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"
/*
	接收者，管理所有的请求链接
*/

class Accepter : public NetHandler
{
public:
	Accepter(NetManager *manager, char *_ip, MsgCallBack *_call_back)
		: NetHandler(manager, NetHandler::ACCEPTER)
		, ip(inet_addr(_ip))
		, call_back(_call_back)
	{}
	~Accepter(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	unsigned long	ip;
	MsgCallBack *	call_back;
private:

};

#endif