
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
	FrameHeader header(frame);

	//��չ����
	if (header.Length() == 126)
	{
		char extend_data[FrameHeader::MID_EXTEND_LEN];
		memcpy(extend_data, frame + FrameHeader::HEADER_LEN, FrameHeader::MID_EXTEND_LEN);
		length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
	}
	else if (header.Length() == 127)
	{
		// ����̫��
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
	unsigned int offset = FrameHeader::HEADER_LEN;
	unsigned int extend_len = FrameHeader::MIN_EXTEND_LEN;
	unsigned int mask_len = 0;

	static char extend_data[FrameHeader::MID_EXTEND_LEN];
	static char mask_data[FrameHeader::MASK_LEN];
	//֡ͷ

	FrameHeader header(frame);

	//��չ����
	if (header.Length() == 126)
	{
		memcpy(extend_data, frame + offset, FrameHeader::MID_EXTEND_LEN);
		extend_len += FrameHeader::MID_EXTEND_LEN;
		length = (unsigned int)extend_data[0] * 256 + (unsigned int)extend_data[1];
	}
	else if (header.Length() == 127)
	{
		// ����̫��
		return false;
	}
	else
	{
		length = header.Length();
	}

	offset += extend_len;

	//�Ƿ�������
	if (header.HasMask())
	{
		memcpy(mask_data, frame + offset, FrameHeader::MASK_LEN);
		mask_len = FrameHeader::MASK_LEN;
	}

	offset += mask_len;
	//��Ϣ��

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
			data[i] = (data[i] ^ data[i % FrameHeader::MASK_LEN]);
		}
	}
	return true;
}


