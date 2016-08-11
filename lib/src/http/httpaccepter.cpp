
#include "httpaccepter.h"
#include "httplistener.h"
#include "3rd/http_parser.h"

int url_call_back(http_parser* p, const char *at, size_t length)
{
	static const char *FIELD = "Url";
	static const int FIELD_LEN = strlen(FIELD);
	((HttpListener *)p->data)->Push(HttpAccepter::CB_CONTENT, FIELD, FIELD_LEN, at, length);
	return 0;
}

int field_call_back(http_parser* p, const char *at, size_t length)
{
	size_t len = length >= HttpListener::MAX_FILED_LEN ? HttpListener::MAX_FILED_LEN - 1 : length;

	memcpy(((HttpListener *)p->data)->field, at, len);
	((HttpListener *)p->data)->field[len] = '\0';
	return 0;
}

int value_call_back(http_parser* p, const char *at, size_t length)
{
	((HttpListener *)p->data)->Push(HttpAccepter::CB_FIELD, ((HttpListener *)p->data)->field, strlen(((HttpListener *)p->data)->field), at, length);
	return 0;
}

int content_call_back(http_parser* p, const char *at, size_t length)
{
	static const char *FIELD = "Content";
	static const int FIELD_LEN = strlen(FIELD);
	((HttpListener *)p->data)->Push(HttpAccepter::CB_CONTENT, FIELD, FIELD_LEN, at, length);
	printf("body_call_back\n");
	return 0;
}

HttpAccepter::HttpAccepter(SocketThread *t, int flag, int size /*= 0*/)
: Accepter(t, NetHandler::HTTP_ACCEPTER)
, m_settings(new http_parser_settings)
{
	http_parser_settings_init(m_settings);

	if (flag & CB_URL) m_settings->on_url = url_call_back;
	if (flag & CB_FIELD)
	{
		m_settings->on_header_field = field_call_back;
		m_settings->on_header_value = value_call_back;
	}
	if (flag & CB_CONTENT) m_settings->on_body = content_call_back;
}

HttpAccepter::~HttpAccepter()
{
	if (m_settings != NULL)
	{
		delete m_settings;
		m_settings = NULL;
	}
}

void HttpAccepter::OnCanRead()
{
	static struct sockaddr_in addr;
	static SOCKET_LEN len = sizeof(struct sockaddr);
	SOCKET new_sock = accept(m_sock, (struct sockaddr*)&addr, &len);
	if (new_sock != INVALID_SOCKET)
	{
		HttpListener *handler = new HttpListener(m_thread, m_settings);
		handler->m_msg_index = m_msg_index;
		handler->m_sock = new_sock;
		handler->m_handle = m_thread->AddNetHandler(handler);
		m_thread->PushGameMsg(handler, BaseMsg::MSG_ACCEPT, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	}
}

