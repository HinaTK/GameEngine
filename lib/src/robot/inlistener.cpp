
#include "inlistener.h"
#include "lib/include/frame/netcommon.h"
#include "lib/include/frame/netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, INListener, 256);

INListener::INListener(SocketThread *t, int size)
: Listener(t)
, buf_size(size)
{

}

bool INListener::RecvBuf()
{
	// 	static int hand = 23;
	// 	static char hand_buf[23];
	// 	if (hand > 0)
	// 	{
	// 		int ret = recv(m_sock, hand_buf, hand, 0);
	// 		if (ret <= 0)
	// 		{
	// 			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
	// 			{
	// 				return true;
	// 			}
	// 			RETUEN_ERROR_2(NetHandler::DR_RECV_BUF, NetCommon::Error());
	// 		}
	// 		hand = hand - ret;
	// 		return this->RecvBuf();
	// 	}
	// 	else
	unsigned int len = m_recv_buf.FreeLength();
	char *buf = m_recv_buf.GetFreeBuf();
	{
		int ret = recv(m_sock, buf, len, 0);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR && NetCommon::Error() == WOULDBLOCK)
			{
				return true;
			}
			RETUEN_ERROR_2(NetHandler::DR_RECV_BUF, NetCommon::Error());
		}
		m_recv_buf.AddLength(ret);
		return this->RecvBuf();
	}
}

bool INListener::AnalyzeBuf()
{
	static const unsigned int SHORT_LEN = sizeof(unsigned short);
	unsigned int data_len = m_recv_buf.Length();
	while (data_len > SHORT_LEN)
	{
		const char *buf = m_recv_buf.GetBuf();
		unsigned short len = *(unsigned short *)(buf);
		if (data_len >= (unsigned int)len && len > 0)
		{
			m_thread->PushData(this, BaseMsg::MSG_RECV, buf + SHORT_LEN, len - SHORT_LEN);
			m_recv_buf.RemoveBuf(len);	
			data_len -= len;
		}
		else return true;
	}
	return true;
	
}


void INListener::Send(const char *buf, unsigned int len)
{
	NetCommon::Header header;
	header.msg_len = len;
	//m_send_buf_write->Push((const char *)&header, NetCommon::HEADER_LENGTH);
	m_send_buf->Push(buf, len);
}




