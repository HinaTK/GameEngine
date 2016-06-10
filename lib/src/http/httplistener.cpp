
#include "httplistener.h"
#include "3rd/http_parser.h"

REGISTER_MEMORYPOOL(memorypool, HttpListener, 32);

int call_back(http_parser* p, const char *at, size_t length)
{
	printf("ddddddd\n");
	if (p->method == HTTP_GET)
	{
		//http_parser_pause(p, 1);
	}
	return 0;
}

int status_call_back(http_parser* p, const char *at, size_t length)
{
	//printf("status_call_back %s\n");
	// 	if (p->method == HTTP_GET)
	// 	{
	// 		http_parser_pause(p, 1);
	// 	}
	return 0;
}

int field_call_back(http_parser* p, const char *at, size_t length)
{
	printf("field_call_back\n");
// 	if (p->method == HTTP_GET)
// 	{
// 		http_parser_pause(p, 1);
// 	}
	return 0;
}

int header_call_back(http_parser* p)
{
	printf("ddddddd123\n");
// 	if (p->method == HTTP_GET)
// 	{
// 		http_parser_pause(p, 1);
// 	}
	return 0;
}

int message_call_back(http_parser* p)
{
	printf("SSSSSSSSSSSSSSSSSS\n");
	// 	if (p->method == HTTP_GET)
	// 	{
	// 		http_parser_pause(p, 1);
	// 	}
	return 0;
}

int body_call_back(http_parser* p, const char *at, size_t length)
{
	printf("body_call_back\n");
	// 	if (p->method == HTTP_GET)
	// 	{
	// 		http_parser_pause(p, 1);
	// 	}
	return 0;
}

HttpListener::HttpListener(SocketThread *t)
: Listener(t)
, parser(new http_parser)
, settings(new http_parser_settings)
, buf_size(0)
{
	http_parser_init(parser, HTTP_REQUEST);
	// todo settings 可以设置成公共的
	http_parser_settings_init(settings);

	settings->on_url = call_back;
	settings->on_status = field_call_back;
	settings->on_header_field = field_call_back;
	settings->on_headers_complete = header_call_back;
	settings->on_message_complete = message_call_back;
	settings->on_body = body_call_back;
}

HttpListener::~HttpListener()
{

}

bool HttpListener::RecvBuf()
{
	if (buf_size < MAX_HTTP_BUF)
	{
		int ret = recv(m_sock, buf + buf_size, MAX_HTTP_BUF - buf_size, 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				return true;
			}
			RETUEN_ERROR(NetHandler::DR_RECV_BUF);
		}
		buf_size += ret;
		return this->RecvBuf();
	}
	RETUEN_ERROR(NetHandler::DR_MSG_TOO_LONG);
}

bool HttpListener::AnalyzeBuf()
{
	static const char buf1[] =
"GET / HTTP/1.1\r\n\
Host: 127.0.0.1:12345\r\n\
Connection: keep-alive\r\n\
Cache-Control: max-age=0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
Upgrade-Insecure-Requests: 1\r\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
Accept-Encoding: gzip, deflate, sdch\r\n\
Accept-Language: zh-CN,zh;q=0.8\r\n\
Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
\r\n";
	static const int buf_size1 = strlen(buf1);

	static const char buf2[] =
"GET / HTTP/1.1\r\n\
Host: 127.0.0.1:12345\r\n\
Connection: keep-alive\r\n\
Cache-Control: max-age=0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
Upgrade-Insecure-Requests: 1\r\n";
	static const int buf_size2 = strlen(buf2);
// 	http_parser_execute(parser, settings, buf2, buf_size2);
// 	printf("result1 %s %s\n", http_errno_name((http_errno)parser->http_errno), http_errno_description((http_errno)parser->http_errno));
// 	
	static const char buf3[] =
"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
Accept-Encoding: gzip, deflate, sdch\r\n\
Accept-Language: zh-CN,zh;q=0.8\r\n\
Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
\r\n\
GET / HTTP/1.1\r\n";
	static const int buf_size3 = strlen(buf3);
// 	http_parser_execute(parser, settings, buf3, buf_size3);
// 	printf("result2 %s %s\n", http_errno_name((http_errno)parser->http_errno), http_errno_description((http_errno)parser->http_errno));
// 	
	static const char buf4[] =
"GET / HTTP/1.1\r\n\
Host: 127.0.0.1:12345\r\n\
Connection: keep-alive\r\n\
Cache-Control: max-age=0\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
Upgrade-Insecure-Requests: 1\r\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
Accept-Encoding: gzip, deflate, sdch\r\n\
Accept-Language: zh-CN,zh;q=0.8\r\n\
Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
Content-Length: 11\r\n\
\r\n\
hello world\r\n";

	static const int buf_size4 = strlen(buf4);

	http_parser_execute(parser, settings, buf4, buf_size4);
	printf("result2 %s %s\n", http_errno_name((http_errno)parser->http_errno), http_errno_description((http_errno)parser->http_errno));

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

