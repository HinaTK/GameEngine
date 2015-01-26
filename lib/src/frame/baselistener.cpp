
#include "baselistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"

REGISTER_MEMORYPOOL(memorypool, BaseListener, 256);

#define CHECK_REMOVE()\
	if (remove_len > 0)\
{\
	m_recv_buf.RemoveBuf(remove_len);\
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
		if (header->msg_len <= 0)
		{
			CHECK_REMOVE();
			return false;
		}

		m_net_manager->GetMsgQueue()->Push(m_net_id, buf + NetCommon::HEADER_LENGTH, header->msg_len - NetCommon::HEADER_LENGTH);

		remove_len += header->msg_len;
		buf_len -= header->msg_len;
		if (buf_len <= NetCommon::HEADER_LENGTH)
		{
			break;
		}
		buf = buf + header->msg_len;
		header = (NetCommon::Header *)buf;
		if (header->msg_len <= NetCommon::HEADER_LENGTH)
		{
			CHECK_REMOVE();
			return false;
		}
	}

	CHECK_REMOVE();
	return true;
}



