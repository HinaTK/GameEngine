
#include "weblistener.h"
#include "netcommon.h"
#include "netmanager.h"
#include "common/socketdef.h"
#include "websocket/dataframeheader.h"

REGISTER_MEMORYPOOL(memorypool, WebListener, 256);

#define CHECK_BUF_LEN()\
	if ( buf_len < (int)buf_offset)\
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
		if (header.Length() < 126)
		{
			length = header.Length();
		}
		else if (header.Length() == 126)
		{
			buf_offset += FrameHeader::MID_EXTEND_LEN;
			CHECK_BUF_LEN();
			frame_offset += FrameHeader::MID_EXTEND_LEN;
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

		if (header.HasMask())
		{
			buf_offset += FrameHeader::MASK_LEN;
			CHECK_BUF_LEN();
			char mask_data[FrameHeader::MASK_LEN];
			memcpy(mask_data, buf + frame_offset, FrameHeader::MASK_LEN);
			frame_offset += FrameHeader::MASK_LEN;

			buf_offset += length;
			CHECK_BUF_LEN();
			char *data = (char *)(buf + frame_offset);
			// 去掉模，效率更快
			int size = length - (length % FrameHeader::MASK_LEN);
			for (int i = 0; i < size; i = i + FrameHeader::MASK_LEN)
			{
				data[i]		= (data[i]		^ mask_data[0]);
				data[i + 1] = (data[i + 1]	^ mask_data[1]);
				data[i + 2] = (data[i + 2]	^ mask_data[2]);
				data[i + 3] = (data[i + 3]	^ mask_data[3]);
			}
			for (int i = size; i < length; ++i)
			{
				data[i] = (data[i] ^ mask_data[i - size]);
			}

			m_net_manager->GetMsgQueue()->Push(m_handle, data, length);
		}
		else
		{
			buf_offset += length;
			CHECK_BUF_LEN();

			m_net_manager->GetMsgQueue()->Push(m_handle, buf + frame_offset, length);
		}
		
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
	unsigned int frame_length = BASE_LEN + len;
	unsigned int offset = FrameHeader::HEADER_LEN;
	unsigned char *frame = (unsigned char *)MemoryVL::Instance().Malloc(frame_length);
	int extend_len = 0;
	if (frame_length < 126)
	{
		ConstructFrameHeader(true, false, false, false, 2, len, frame);
	}
	else if (frame_length < 65536)
	{
		ConstructFrameHeader(true, false, false, false, 2, 126, frame);
		extend_len = (int)FrameHeader::MID_EXTEND_LEN;
		*(frame + offset) = len / 256;
		*(frame + offset + 1) = len % 256;
	}
	else
	{
		ConstructFrameHeader(true, false, false, false, 2, 127, frame);
		extend_len = (int)FrameHeader::MAX_EXTEND_LEN;
		unsigned int left = len;
		for (int i = extend_len - 1; i >= 0; --i)
		{
			*(frame + offset + i) = (unsigned char)(left % 256);
			left = left / 256;

			if (left == 0) break;
		}
	}
	
	offset += extend_len;

	// 不用mask,这里不处理mask数据

	memcpy(frame + offset, buf, len);
	{
		MutexLock ml(&m_send_mutex);
		m_send_buf_write->Push((char *)frame, offset + len);
	}
	
	MemoryVL::Instance().Free(frame);
}