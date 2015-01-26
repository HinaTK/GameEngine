
#include "websocket/recvframe.h"
#include "websocket/dataframeheader.h"
// #include "libcommon/memorypool.h"
// 
// REGISTER_MEMORYPOOL(memorypool, RecvFrame, 64);

RecvFrame::RecvFrame()
{
	
}

RecvFrame::~RecvFrame()
{
	//MemoryVL::Instance().Free(data_frame);
}

bool RecvFrame::CheckHeader( const char *frame )
{
	DataFrameHeader header(frame);

	//扩展长度
	if (header.Length() == 126)
	{
		char extend_data[DataFrameHeader::MID_EXTEND_LEN];
		memcpy(extend_data, frame + DataFrameHeader::HEADER_LEN, DataFrameHeader::MID_EXTEND_LEN);
		length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
	}
	else if (header.Length() == 127)
	{
		// 数据太大
		return false;
	}
	else
	{
		length = header.Length();
	}
	return true;
}

bool RecvFrame::Frame( const char *frame )
{
	unsigned int offset = DataFrameHeader::HEADER_LEN;
	unsigned int extend_len = DataFrameHeader::MIN_EXTEND_LEN;
	unsigned int mask_len = 0;

	static char extend_data[DataFrameHeader::MID_EXTEND_LEN];
	static char mask_data[DataFrameHeader::MASK_LEN];
	//帧头

	DataFrameHeader header(frame);

	//扩展长度
	if (header.Length() == 126)
	{
		memcpy(extend_data, frame + offset, DataFrameHeader::MID_EXTEND_LEN);
		extend_len += DataFrameHeader::MID_EXTEND_LEN;
		length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
	}
	else if (header.Length() == 127)
	{
		// 数据太大
		return false;
	}
	else
	{
		length = header.Length();
	}

	offset += extend_len;

	//是否有掩码
	if (header.HasMask())
	{
		memcpy(mask_data, frame + offset, DataFrameHeader::MASK_LEN);
		mask_len = DataFrameHeader::MASK_LEN;
	}

	offset += mask_len;
	//消息体

// 	if (extend_len == DataFrameHeader::MIN_EXTEND_LEN)
// 	{
// 		m_data_length = header.Length();
// 	}
// 	else if (extend_len == DataFrameHeader::MID_EXTEND_LEN)
// 	{
// 		m_data_length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
// 	}
// 	else
// 	{
// 		// 		long len = 0;
// 		// 		int n = 1;
// 		// 		for (int i = 7; i >= 0; i--)
// 		// 		{
// 		// 			len += (int)_extend[i] * n;
// 		// 			n *= 256;
// 		// 		}
// 		// 		_content = new byte[len];
// 		// 		Buffer.BlockCopy(buffer, _extend.Length + _mask.Length + 2, _content, 0, _content.Length);
// 		return false;
// 	}

	memcpy(data, frame + offset, length);
	if (header.HasMask())
	{
		for (unsigned int i = 0; i < length; i++)
		{
			data[i] = (data[i] ^ data[i % DataFrameHeader::MASK_LEN]);
		}
	}
	return true;
}


