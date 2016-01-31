
#include "baselistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, BaseListener, 256);

BaseListener::BaseListener(NetManager *manager, int size)
: Listener(manager)
, buf_size(size)
{

}

int BaseListener::AnalyzeBuf()
{
	const char *buf = m_recv_buf.GetBuf();	
	int buf_len = (int)m_recv_buf.Length();
	if (buf_len <= NetCommon::HEADER_LENGTH)
	{
		return 0;
	}

	NetCommon::Header *header = (NetCommon::Header *)buf;
	unsigned int remove_len = 0;
	while (header->msg_len <= buf_len)
	{
		if (header->msg_len <= 0)
		{
			// 数据错误
			return NetHandler::DR_HEADER_TOO_SMALL;
		}

		if (header->msg_len > buf_size && buf_size > 0)
		{
			// 返回错误码
			return NetHandler::DR_HEADER_TOO_BIG;
		}
		buf += NetCommon::HEADER_LENGTH;
		m_net_manager->PushMsg(this, BaseMsg::MSG_RECV, buf, header->msg_len);

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
	return 0;
}

void BaseListener::Send( const char *buf, unsigned int len )
{
	NetCommon::Header header;
	header.msg_len = len;

	MutexLock ml(&m_send_mutex);
	m_send_buf_write->Push((const char *)&header, NetCommon::HEADER_LENGTH);
	m_send_buf_write->Push(buf, len);
}




