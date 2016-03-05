
#ifndef DATA_FRAME_HEADER_H
#define DATA_FRAME_HEADER_H

/*
WebSocket数据帧结构如下图所示：
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+---------------------------+
|F|R|R|R|opcod|M| Payload len   | Extended payload length		|
|I|S|S|S|e(4) |A| (7)           | (16 / 64)						|
|N|V|V|V|     |S|               | (if payload len == 126 / 127) |
| |1|2|3|     |K|               |								|
+-+-+-+-+-----+-+---------------+-------------------------------+
| Extended payload length continued, if payload len == 127		|
+-------------------------------+-------------------------------+
|								| Masking - key,if MASK set to 1|
+-------------------------------+-------------------------------+
| Masking - key(continued)		| Payload Data					|
+-------------------------------+-------------------------------+
|                     Payload Data continued ...				|
+---------------------------------------------------------------+
|					  Payload Data continued ...				|
+---------------------------------------------------------------+

OPCODE：4位
解释PayloadData，如果接收到未知的opcode，接收端必须关闭连接。
0x0表示附加数据帧
0x1表示文本数据帧
0x2表示二进制数据帧
0x3-7暂时无定义，为以后的非控制帧保留
0x8表示连接关闭
0x9表示ping
0xA表示pong
0xB-F暂时无定义，为以后的控制帧保留
*/

class FrameHeader
{
public:
	static const unsigned int MIN_EXTEND_LEN = 0;
	static const unsigned int MID_EXTEND_LEN = 2;
	static const unsigned int MAX_EXTEND_LEN = 8;
	static const unsigned int HEADER_LEN = 2;
	static const unsigned int MASK_LEN = 4;

	~FrameHeader(){};
	FrameHeader(const char *buffer);

	unsigned char	Length(){ return m_payloadlength; }
	
	bool			HasMask(){ return m_maskcode; }

private:
	//DataFrameHeader(){}
	bool			m_fin;
	bool			m_rsv1;
	bool			m_rsv2;
	bool			m_rsv3;
	char			m_opcode;
	bool			m_maskcode;
	unsigned char	m_payloadlength;

};

// 构造帧头
void ConstructFrameHeader(bool fin, bool rsv1, bool rsv2, bool rsv3, char opcode, unsigned char length, unsigned char *data, bool hasmask = false);

#endif