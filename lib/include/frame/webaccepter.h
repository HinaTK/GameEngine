
#ifndef WEB_ACCEPTER_H
#define WEB_ACCEPTER_H

#include "accepter.h"

class WebAccepter : public Accepter
{
public:
	WebAccepter(NetManager *manager);
	virtual ~WebAccepter(){};

	virtual void	OnCanRead();

protected:
	

};

#endif