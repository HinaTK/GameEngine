
#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H

#include "frame/listener.h"

struct http_parser;
struct http_parser_settings;
class HttpListener : public Listener
{
public:
	static const int MAX_HTTP_BUF = 4096;
	HttpListener(SocketThread *t);
	virtual ~HttpListener();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	void			Send(const char *buf, unsigned int len);
protected:
	virtual bool	RecvBuf();
	virtual bool	AnalyzeBuf();

private:
	http_parser *parser;
	http_parser_settings *settings;
	char	buf[HttpListener::MAX_HTTP_BUF];
	int		buf_size;
};

#endif // !HTTP_LISTENER_H
