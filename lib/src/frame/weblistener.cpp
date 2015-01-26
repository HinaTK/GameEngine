
#include "weblistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"
#include "websocket/recvframe.h"
#include "websocket/dataframeheader.h"


#define CHECK_BUF_LEN()\
	if ( buf_len <= (int)buf_offset)\
	{\
		if (remove_len > 0)\
		{\
			m_recv_buf.RemoveBuf(remove_len);\
		}\
		return true;\
	}

// websocket 在数据中不用加协议头
bool WebListener::AnalyzeBuf()
{
	//static char extend_data[DataFrameHeader::MID_EXTEND_LEN];
	//static char mask_data[DataFrameHeader::MASK_LEN];
	static int length = 0;
	unsigned int remove_len = 0;
	int buf_len = (int)m_recv_buf.Length();
	do 
	{
		unsigned int buf_offset = FrameHeader::HEADER_LEN;
		unsigned int frame_offset = FrameHeader::HEADER_LEN;
		CHECK_BUF_LEN();
		const char *buf = m_recv_buf.GetBuf();
		FrameHeader header(buf);
		if (header.Length() == 126)
		{
			buf_offset += FrameHeader::MID_EXTEND_LEN;
			CHECK_BUF_LEN();
			//memcpy(extend_data, buf + frame_offset, DataFrameHeader::MID_EXTEND_LEN);
			frame_offset += FrameHeader::MID_EXTEND_LEN;
			//length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
			length = (unsigned int)*(buf + frame_offset) * 256 + (unsigned int)*(buf + frame_offset + 1);
		}
		else if (header.Length() == 127)
		{
			if (remove_len > 0)
			{
				m_recv_buf.RemoveBuf(remove_len);
			}
			return false; // 数据太大,断开链接
		}
		else
		{
			length = header.Length();
		}

		if (header.HasMask())
		{
			buf_offset += FrameHeader::MASK_LEN;
			CHECK_BUF_LEN();
			//memcpy(mask_data, buf + frame_offset, DataFrameHeader::MASK_LEN);
			frame_offset += FrameHeader::MASK_LEN;
		}

		buf_offset += length;
		CHECK_BUF_LEN();
		m_net_manager->GetMsgQueue()->Push(m_net_id, buf + frame_offset, length);
		buf_len -= buf_offset;
		remove_len += buf_offset;
		//m_recv_buf.RemoveBuf(buf_offset);
	} while (true);
	if (remove_len > 0)
	{
		m_recv_buf.RemoveBuf(remove_len);
	}
	return true;
}

void WebListener::Send(const char *buf, unsigned int len)
{
	// 构造websocket发送帧
	static const unsigned int BASE_LEN = FrameHeader::HEADER_LEN + FrameHeader::MAX_EXTEND_LEN + FrameHeader::MASK_LEN;
	MemoryVL::MemoryInfo frame;
	unsigned int frame_length = BASE_LEN + len;
	unsigned int offset = FrameHeader::HEADER_LEN;
	if (!MemoryVL::Instance().Malloc(frame_length, frame))
	{
		return;
	}
	int extend_len = 0;
	if (frame_length < 126)
	{
		ConstructFrameHeader(true, false, false, false, 1, frame_length, frame.mem);	
	}
	else if (frame_length < 65536)
	{
		ConstructFrameHeader(true, false, false, false, 1, 126, frame.mem);
		extend_len = (int)FrameHeader::MID_EXTEND_LEN;
		*(frame.mem + offset) = len / 256;
		*(frame.mem + offset + 1) = len % 256;
	}
	else
	{
		ConstructFrameHeader(true, false, false, false, 1, 127, frame.mem);
		extend_len = (int)FrameHeader::MAX_EXTEND_LEN;
		unsigned int left = len;
		for (int i = extend_len - 1; i >= 0; --i)
		{
			*(frame.mem + offset + i) = (byte)(left % 256);
			left = left / 256;

			if (left == 0) break;
		}
	}
	
	offset += extend_len;

	// 不用mask,这里不处理mask数据

	memcpy(frame.mem + offset, buf, len);
	{
		MutexLock ml(&m_send_mutex);
		m_send_buf_write->Push(frame.mem, offset + len);
	}
	
	MemoryVL::Instance().Free(frame);
}