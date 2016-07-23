
#include "httplistener.h"
#include "3rd/http_parser.h"

REGISTER_SAFE_MEMORYPOOL(memorypool, HttpListener, 32);

/*
	todo
	用flag来标明哪些数据需要被获取;
	1:url
	2:field
	4:content

	最终拆成field value(字符串)，放到消息队列中，再由监听线程获取

	测试数据包截断（不是以\r\n截断）
*/

//todo 预先搞一个http_parser对象池

HttpListener::HttpListener(SocketThread *t, http_parser_settings *settings)
: Listener(t)
, m_parser(new http_parser)
, m_settings(settings)
, m_buf_size(0)
{
	http_parser_init(m_parser, HTTP_REQUEST);
	m_parser->data = this;
}

HttpListener::~HttpListener()
{
	if (m_parser != NULL)
	{
		delete m_parser;
		m_parser = NULL;
	}
}

bool HttpListener::RecvBuf()
{
	if (m_buf_size < MAX_HTTP_BUF)
	{
		int ret = recv(m_sock, m_buf + m_buf_size, MAX_HTTP_BUF - m_buf_size, 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				return true;
			}
			RETUEN_ERROR_2(NetHandler::DR_RECV_BUF, NetCommon::Error());
		}
		m_buf_size += ret;
		return this->RecvBuf();
	}
	RETUEN_ERROR(NetHandler::DR_MSG_TOO_LONG);
}

bool HttpListener::AnalyzeBuf()
{
	http_parser_execute(m_parser, m_settings, m_buf, m_buf_size);
	if ((http_errno)m_parser->http_errno != HPE_OK)
	{
		RETUEN_ERROR_2(HttpListener::DR_HTTP_PARSE, m_parser->http_errno);
	}
	return true;
}
// bool HttpListener::AnalyzeBuf()
// {
// // 	static const char buf1[] =
// // "GET / HTTP/1.1\r\n\
// // Host: 127.0.0.1:12345\r\n\
// // Connection: keep-alive\r\n\
// // Cache-Control: max-age=0\r\n\
// // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
// // Upgrade-Insecure-Requests: 1\r\n\
// // User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
// // Accept-Encoding: gzip, deflate, sdch\r\n\
// // Accept-Language: zh-CN,zh;q=0.8\r\n\
// // Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
// // \r\n";
// // 	static const int buf_size1 = strlen(buf1);
// 
// 	static const char buf2[] =
// "GET / HTTP/1.1\r\n\
// Host: 127.0.0.1:12345\r\n\
// Connection: keep-alive\r\n\
// Cache-Control: max-age=0\r\n\
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
// Upgrade-Insecure-Requests: 1\r\n\
// User-";
// 	static const int buf_size2 = strlen(buf2);
// 	http_parser_execute(m_parser, m_settings, buf2, buf_size2);
// 	printf("result1 %s %s\n", http_errno_name((http_errno)m_parser->http_errno), http_errno_description((http_errno)m_parser->http_errno));
// 	
// 	static const char buf3[] =
// "Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
// Accept-Encoding: gzip, deflate, sdch\r\n\
// Accept-Language: zh-CN,zh;q=0.8\r\n\
// Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
// \r\n\
// GET / HTTP/1.1\r\n";
// 	static const int buf_size3 = strlen(buf3);
// 	http_parser_execute(m_parser, m_settings, buf3, buf_size3);
// 	printf("result2 %s %s\n", http_errno_name((http_errno)m_parser->http_errno), http_errno_description((http_errno)m_parser->http_errno));
// 	
// // 	static const char buf4[] =
// // "GET / HTTP/1.1\r\n\
// // Host: 127.0.0.1:12345\r\n\
// // Connection: keep-alive\r\n\
// // Cache-Control: max-age=0\r\n\
// // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\
// // Upgrade-Insecure-Requests: 1\r\n\
// // User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.106 Safari/537.36\r\n\
// // Accept-Encoding: gzip, deflate, sdch\r\n\
// // Accept-Language: zh-CN,zh;q=0.8\r\n\
// // Cookie: __utma=96992031.1932631234.1423383291.1423383291.1423383291.1\r\n\
// // Content-Length: 11\r\n\
// // \r\n\
// // hello world\r\n";
// // 
// // 	static const int buf_size4 = strlen(buf4);
// // 
// // 	http_parser_execute(parser, settings, buf4, buf_size4);
// // 	printf("result2 %s %s\n", http_errno_name((http_errno)parser->http_errno), http_errno_description((http_errno)parser->http_errno));
// 
// 	return true;
// }


void HttpListener::Push(int type, const char *field, unsigned int len1, const char *value, unsigned int len2)
{
	static const int TYPE_SIZE = sizeof(int);
	// todo 判断len 是否合法
	GameMsg *msg = m_thread->CreateGameMsg(this->m_msg_index, BaseMsg::MSG_RECV, this->m_handle, TYPE_SIZE + HttpListener::MAX_FILED_LEN + len2);
	*(int *)msg->data = type;
	memcpy(msg->data + TYPE_SIZE, field, len1);
	memcpy(msg->data + TYPE_SIZE + HttpListener::MAX_FILED_LEN, value, len2);
	m_thread->PushGameMsg(msg);
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

