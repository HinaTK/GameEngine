
#include <stdio.h>
#include "handshaker.h"
#include "weblistener.h"
#include "netmanager.h"
#include "netcommon.h"
#include "common/socketdef.h"
#include "websocket/sha1.h"
#include "websocket/base64.h"

REGISTER_MEMORYPOOL(memorypool, HandShaker, 64);

class HandShakeInfo
{
public:
	HandShakeInfo()
	{
		header		= "Sec-WebSocket-Version:";
		key			= "Sec-WebSocket-Key: ";
		magic_key	= "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

		handshake = "HTTP/1.1 101 Switching Protocols\r\n";
		handshake += "Upgrade: WebSocket\r\n";
		handshake += "Connection: Upgrade\r\n";
		handshake += "Sec-WebSocket-Accept: %s\r\n";
		handshake += "\r\n";
	}
	std::string header;
	std::string key;
	std::string magic_key;
	std::string handshake;
};



void HandShaker::OnCanRead()
{
	// 处理握手协议
	if (!HandShake())
	{
		m_net_manager->RemoveHandler(m_handle);
		return;
	}
}

bool HandShaker::HandShake()
{
	static const HandShakeInfo ws;
	char recv_buf[MAX_EXTERNAL_BUF] = { 0 };
	int msg_len = recv(m_sock, recv_buf, MAX_EXTERNAL_BUF, 0);
	if (msg_len <= 0)
	{
		return false;
	}
	
	std::string		recv_str(recv_buf);
	int pos = recv_str.find(ws.header);
	if (pos >= 0)
	{
		pos = recv_str.find(ws.key);
		if (pos >= 0)
		{
			recv_str = recv_str.substr(pos + ws.key.length());
			std::string key_str = recv_str;
			int key_pos = recv_str.find("\r\n");
			if (key_pos > 0)
			{
				key_str = recv_str.substr(0, key_pos);
			}
			std::string server_str = key_str + ws.magic_key;
			SHA1Context sha1;
			int err = SHA1Reset(&sha1);
			if (err)
			{
				return false;
			}
			err = SHA1Input(&sha1, (const unsigned char *)server_str.c_str(), server_str.length());
			if (err)
			{
				return false;
			}
			unsigned char sha1_hash[20];
			err = SHA1Result(&sha1, sha1_hash);
			if (err)
			{
				return false;
			}
			Base64 base64;
			std::string accept_key = base64.Encode(sha1_hash, sizeof(sha1_hash));
			sprintf(m_handshake_data, ws.handshake.c_str(), accept_key.c_str());
			m_data_length = (int)strlen(m_handshake_data);

#ifdef WIN32
			FD_SET(m_sock, m_net_manager->GetWriteSet());
			//FD_SET(m_net_id, m_net_manager->GetReadSet());
#endif // !WIN32

#ifdef __unix
			struct epoll_event ev;
			ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
			ev.data.ptr = (void *)this;
			if (epoll_ctl(m_net_manager->GetEpollFD(), EPOLL_CTL_MOD, m_sock, &ev) == -1)
			{
				// 注册写失败
			}
#endif		
		}
	}
	return true;
}

void HandShaker::OnCanWrite()
{
	while (true)
	{
		int ret = NetCommon::Send(m_sock, m_handshake_data + m_send_length, m_data_length);
		if (ret == SOCKET_ERROR)
		{
			if (NetCommon::Error() == WOULDBLOCK)
			{
				// 缓冲区已经满
				break;
			}
			m_net_manager->RemoveHandler(m_handle);
			return;
		}

		m_data_length -= ret;
		if (m_data_length <= 0)
		{
			WebListener *handler = new WebListener(m_net_manager, NetHandler::LISTENER);
			handler->m_sock = m_sock;
			handler->m_handle = m_handle;	// 用于删除原来的handle
			m_net_manager->AddReplaceHandler(handler);
			return;
		}
		m_send_length += ret;
	}
}
