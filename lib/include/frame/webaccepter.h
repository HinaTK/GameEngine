
#ifndef WEB_ACCEPTER_H
#define WEB_ACCEPTER_H

#include "accepter.h"

class WebAccepter : public Accepter
{
public:
	WebAccepter(NetManager *manager, MsgCallBack *call_back) 
		: Accepter(manager, call_back, NetHandler::WEB_ACCEPTER){};
	~WebAccepter(){};

	virtual void	OnCanRead();

protected:
	

};

#endif