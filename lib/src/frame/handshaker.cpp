
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
		// 删除
		m_net_manager->RemoveHandler(m_handle);
		return;
	}

	WebListener *handler = new WebListener(m_net_manager, NetHandler::LISTENER);
	m_net_manager->ReplaceHandler(m_handle, handler);
}

bool HandShaker::HandShake()
{
	static const HandShakeInfo ws;
	char recv_buf[MAX_EXTERNAL_BUF] = { 0 };
	int msg_len = recv(m_net_id, recv_buf, MAX_EXTERNAL_BUF, 0);
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
				// fprintf(stderr, "SHA1Reset Error %d.\n", err);
				return false;
			}
			err = SHA1Input(&sha1, (const unsigned char *)server_str.c_str(), server_str.length());
			if (err)
			{
				// fprintf(stderr, "SHA1Input Error %d.\n", err);
				return false;
			}
			unsigned char sha1_hash[20];
			err = SHA1Result(&sha1, sha1_hash);
			if (err)
			{
				// fprintf(stderr, "SHA1Result Error %d, could not compute message digest.\n", err);
				return false;
			}
			Base64 base64;
			std::string accept_key = base64.Encode(sha1_hash, sizeof(sha1_hash));
			char handshake[256] = { 0 };
			sprintf(handshake, ws.handshake.c_str(), accept_key.c_str());
			// 这里不应该直接发送
			if (send(m_net_id, handshake, strlen(handshake), 0) == -1)
			{
				return false;
			}
		}
	}
	return true;
}
