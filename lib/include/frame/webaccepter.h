
#ifndef WEB_ACCEPTER_H
#define WEB_ACCEPTER_H

#include "accepter.h"

class WebAccepter : public Accepter
{
public:
	WebAccepter(NetManager *manager) 
		: Accepter(manager, NetHandler::WEB_ACCEPTER){};
	~WebAccepter(){};

	virtual void	OnCanRead();

protected:
	

};

#endif