
#ifndef WEB_ACCEPTER_H
#define WEB_ACCEPTER_H

#include "nethandler.h"

class WebAccepter : public NetHandler
{
public:
	WebAccepter(NetManager *manager, MsgCallBack *_call_back) 
		: NetHandler(manager, NetHandler::WEB_ACCEPTER)
		, call_back(_call_back){};
	~WebAccepter(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);

protected:
	MsgCallBack *call_back;

};

#endif