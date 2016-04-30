
#include "baselistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, BaseListener, 256);

BaseListener::BaseListener(SocketThread *t, int size)
: Listener(t)
, buf_size(size)
{

}

bool BaseListener::AnalyzeBuf()
{
	const char *buf = m_recv_buf.GetBuf();	
	int buf_len = (int)m_recv_buf.Length();
	if (buf_len <= NetCommon::HEADER_LENGTH)
	{
		return true;
	}

	NetCommon::Header *header = (NetCommon::Header *)buf;
	unsigned int remove_len = 0;
	while (header->msg_len <= buf_len)
	{
		if (header->msg_len <= 0) { m_err = NetHandler::DR_HEADER_TOO_SMALL; return false; }
		if (header->msg_len > buf_size && buf_size > 0) { m_err = NetHandler::DR_HEADER_TOO_BIG; return false; }

		buf += NetCommon::HEADER_LENGTH;
		m_thread->PushData(this, BaseMsg::MSG_RECV, buf, header->msg_len);

		remove_len = remove_len + NetCommon::HEADER_LENGTH + header->msg_len;
		buf_len = buf_len - NetCommon::HEADER_LENGTH - header->msg_len;
		if (buf_len <= NetCommon::HEADER_LENGTH)
		{
			break;
		}
		buf += header->msg_len;
		header = (NetCommon::Header *)buf;
	}

	if (remove_len > 0)
	{
		m_recv_buf.RemoveBuf(remove_len); 
	}
	return true;
}

void BaseListener::Send( const char *buf, unsigned int len )
{
	NetCommon::Header header;
	header.msg_len = len;

	MutexLock ml(&m_send_mutex);
	m_send_buf_write->Push((const char *)&header, NetCommon::HEADER_LENGTH);
	m_send_buf_write->Push(buf, len);
}




