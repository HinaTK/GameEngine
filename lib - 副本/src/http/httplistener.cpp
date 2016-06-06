
#include "httplistener.h"
#include "3rd/http_parser.h"

REGISTER_MEMORYPOOL(memorypool, HttpListener, 32);

HttpListener::HttpListener(SocketThread *t, int size)
: Listener(t)
, buf_size(size)
{

}

HttpListener::~HttpListener()
{

}


int call_back(http_parser* p, const char *at, size_t length)
{
	printf("ddddddd\n");
	if (p->method == HTTP_GET)
	{
		//http_parser_pause(p, 1);
	}
	return 0;
}

int call_back2(http_parser* p, const char *at, size_t length)
{
	printf("ddddddd123\n");
	if (p->method == HTTP_GET)
	{
		http_parser_pause(p, 1);
	}
	return length;
}

int call_back3(http_parser* p)
{
	printf("ddddddd123\n");
	if (p->method == HTTP_GET)
	{
		http_parser_pause(p, 1);
	}
	return 1;
}

bool HttpListener::AnalyzeBuf()
{
	http_parser *parser = new http_parser;
	http_parser_init(parser, HTTP_REQUEST);

	http_parser_settings *settings = new http_parser_settings;
	http_parser_settings_init(settings);

	settings->on_url = call_back;
	settings->on_status = call_back2;
	settings->on_header_field = call_back2;
	settings->on_headers_complete = call_back3;
	settings->on_message_complete = call_back3;
	const char *buf = m_recv_buf.GetBuf();
	http_parser_execute(parser, settings, m_recv_buf.GetBuf(), m_recv_buf.Length());
	return true;
}

void HttpListener::Send(const char *buf, unsigned int len)
{
	static const char base[] = 
"HTTP/1.1 200 OK\r\n\
Content-Length: %d\r\n\
\r\n\
%s\r\n";
	// todo 动态在内存池中分配大小
	char new_buf[1024];
	int new_len = sprintf_s(new_buf, base, len, buf);
	MutexLock ml(&m_send_mutex);
	m_send_buf_write->Push(new_buf, new_len);
}

