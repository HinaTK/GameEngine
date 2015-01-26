
#include <stdio.h>
#include <string.h>
#include "websocket/dataframe.h"
#include "websocket/dataframeheader.h"

DataFrame::DataFrame()
: m_extend_len(0)
, m_mask_len(0)
, m_data_len(0)
{
	memset(m_data, 0, sizeof(m_data));
}


DataFrame::DataFrame(const char *buffer)
: m_extend_len(0)
, m_mask_len(0)
, m_data_len(0)
{
// 	memset(m_content, 0, sizeof(m_content));
// 	unsigned int offset = 0;
// 	//帧头
// 
// 	DataFrameHeader header(buffer, offset);
// 
// 	//扩展长度
// 	if (header.Length() == 126)
// 	{
// 		memcpy(m_extend, buffer + offset, MID_EXTEND_LEN);
// 		m_extend_len += MID_EXTEND_LEN;
// 	}
// 	else if (header.Length() == 127)
// 	{
// 		memcpy(m_extend, buffer + offset, MAX_EXTEND_LEN);
// 		m_extend_len += MAX_EXTEND_LEN;
// 	}
// 
// 	offset += m_extend_len;
// 
// 	//是否有掩码
// 	if (header.HasMask())
// 	{
// 		memcpy(m_mask, buffer + offset, MASK_LEN);
// 		m_mask_len = MASK_LEN;
// 	}
// 
// 	offset += m_mask_len;
// 	//消息体
// 	if (m_extend_len == 0)
// 	{
// 		m_content_len = header.Length();
// 	}
// 	else if (m_extend_len == MIN_EXTEND_LEN)
// 	{
// 		m_content_len = (unsigned int)m_extend[0] * 256 + (unsigned int)m_extend[1];
// 	}
// 	else
// 	{
// 		printf("数据太大\n");
// // 		long len = 0;
// // 		int n = 1;
// // 		for (int i = 7; i >= 0; i--)
// // 		{
// // 			len += (int)_extend[i] * n;
// // 			n *= 256;
// // 		}
// // 		_content = new byte[len];
// // 		Buffer.BlockCopy(buffer, _extend.Length + _mask.Length + 2, _content, 0, _content.Length);
// 	}
// 
// 	memcpy(m_content, buffer + offset, m_content_len);
// 	if (header.HasMask())
// 	{
// 		Mask();
// 	}
	
}

void DataFrame::Mask()
{
	for (unsigned int i = 0; i < m_data_len; i++)
	{
		m_data[i] = (m_data[i] ^ m_mask[i % MASK_LEN]);
	}
}

bool DataFrame::FromRecvFrame( const char *msg )
{
	return true;
}

void DataFrame::ToSendFrame(const char* src, unsigned int src_len, char* des, unsigned int &des_len, bool mask, bool init_data)
{
	if (src_len < 126)
	{
		DataFrameHeader header(true, false, false, false, 1, mask, src_len);
		header.Header(des);
	}
	else if (src_len < 65536)
	{
		DataFrameHeader header(true, false, false, false, 1, mask, 126);
		header.Header(des);
		m_extend_len = MID_EXTEND_LEN;
	}
	else
	{
		// 数据太大
		// DataFrameHeader header(true, false, false, false, 1, false, 127);
		return;
	}
	
	memcpy(des + HEADER_LEN, m_extend, m_extend_len);
	if (mask)
	{
		memcpy(des + HEADER_LEN + m_extend_len, m_mask, MASK_LEN);
		m_mask_len = MASK_LEN;
	}
	memcpy(des + HEADER_LEN + m_extend_len + m_mask_len, src, src_len);
	if (init_data)
	{
		memcpy(m_data, src, src_len);
	}
	des_len = HEADER_LEN + m_extend_len + m_mask_len + src_len;
}

