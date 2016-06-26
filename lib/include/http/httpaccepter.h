
#ifndef HTTP_ACCEPTER_H
#define HTTP_ACCEPTER_H

#include "lib/include/frame/accepter.h"

struct http_parser_settings;
class HttpAccepter : public Accepter
{
public:
	HttpAccepter(SocketThread *t, int flag, int size = 0);
	virtual ~HttpAccepter();

	// »Øµ÷
	enum
	{
		CB_URL		= 1,
		CB_FIELD	= 2,
		CB_CONTENT	= 4
	};

	virtual void	OnCanRead();

private:
	http_parser_settings *m_settings;
};

#endif