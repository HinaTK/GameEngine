
#include <string.h>
#include "websocket/dataframeheader.h"

FrameHeader::FrameHeader(const char *buffer)
{
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


void ConstructFrameHeader(bool fin, bool rsv1, bool rsv2, bool rsv3, char opcode, unsigned char length, unsigned char *data, bool hasmask /*= false*/)
{
	memset(data, 0, 2);

	if (fin) data[0] ^= 0x80;
	if (rsv1) data[0] ^= 0x40;
	if (rsv2) data[0] ^= 0x20;
	if (rsv3) data[0] ^= 0x10;

	data[0] ^= opcode;

	if (hasmask) data[1] ^= 0x80;

	data[1] ^= length;
}
