
#include "websocket/dataframeheader.h"

DataFrameHeader::DataFrameHeader(const char *buffer)
{
	// 		if (buffer.Length < 2)
	// 			throw new Exception("无效的数据头.");

	//第一个字节
	m_fin = (buffer[0] & 0x80) == 0x80;
	m_rsv1 = (buffer[0] & 0x40) == 0x40;
	m_rsv2 = (buffer[0] & 0x20) == 0x20;
	m_rsv3 = (buffer[0] & 0x10) == 0x10;
	m_opcode = (buffer[0] & 0x0f);

	//第二个字节
	m_maskcode = (buffer[1] & 0x80) == 0x80;
	m_payloadlength = (buffer[1] & 0x7f);
	
}

DataFrameHeader::DataFrameHeader(bool fin, bool rsv1, bool rsv2, bool rsv3, char opcode, bool hasmask, unsigned char length)
{
	m_fin = fin;
	m_rsv1 = rsv1;
	m_rsv2 = rsv2;
	m_rsv3 = rsv3;
	m_opcode = opcode;
	//第二个字节
	m_maskcode = hasmask;
	m_payloadlength = length;
}

void DataFrameHeader::Header(char buffer[2])
{
	memset(buffer, 0, sizeof(buffer));

	if (m_fin) buffer[0] ^= 0x80;
	if (m_rsv1) buffer[0] ^= 0x40;
	if (m_rsv2) buffer[0] ^= 0x20;
	if (m_rsv3) buffer[0] ^= 0x10;

	buffer[0] ^= m_opcode;

	if (m_maskcode) buffer[1] ^= 0x80;

	buffer[1] ^= m_payloadlength;
}

