
#ifndef HTTP_LISTENER_H
#define HTTP_LISTENER_H

#include "frame/listener.h"

struct http_parser;
struct http_parser_settings;
class HttpListener : public Listener
{
public:
	static const int MAX_HTTP_BUF = 4096;
	static const int MAX_FILED_NAME = 32;
	HttpListener(SocketThread *t, http_parser_settings *settings);
	virtual ~HttpListener();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	// disconnect reason
	enum
	{
		DR_HTTP_PARSE = NetHandler::DR_CUSTOM
	};
	void			Send(const char *buf, unsigned int len);

	void			Push(const char *field, const char *value);
protected:
	virtual bool	RecvBuf();
	virtual bool	AnalyzeBuf();

public:
	char	field[HttpListener::MAX_FILED_NAME + 1];
private:
	http_parser *m_parser;
	http_parser_settings *m_settings;
	char	m_buf[HttpListener::MAX_HTTP_BUF];
	int		m_buf_size;
};

#endif // !HTTP_LISTENER_H
