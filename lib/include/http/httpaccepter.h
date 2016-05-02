
#ifndef HTTP_ACCEPTER_H
#define HTTP_ACCEPTER_H

#include "lib/include/frame/accepter.h"

class HttpAccepter : public Accepter
{
public:
	HttpAccepter(SocketThread *t, int size = 0);
	virtual ~HttpAccepter();

	virtual void	OnCanRead();
private:
	int buf_size;
};

#endif