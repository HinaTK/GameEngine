
#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H

#include "frame/listener.h"

class HttpListener : public Listener
{
public:
	HttpListener(SocketThread *t, int size = 0);
	virtual ~HttpListener();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual bool	AnalyzeBuf();
	int		buf_size;
};

#endif // !HTTP_LISTENER_H
