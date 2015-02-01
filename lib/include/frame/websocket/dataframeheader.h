
#ifndef DATA_FRAME_HEADER_H
#define DATA_FRAME_HEADER_H

/*
WebSocket����֡�ṹ����ͼ��ʾ��
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

OPCODE��4λ
����PayloadData��������յ�δ֪��opcode�����ն˱���ر����ӡ�
0x0��ʾ��������֡
0x1��ʾ�ı�����֡
0x2��ʾ����������֡
0x3-7��ʱ�޶��壬Ϊ�Ժ�ķǿ���֡����
0x8��ʾ���ӹر�
0x9��ʾping
0xA��ʾpong
0xB-F��ʱ�޶��壬Ϊ�Ժ�Ŀ���֡����
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

// ����֡ͷ
void ConstructFrameHeader(bool fin, bool rsv1, bool rsv2, bool rsv3, char opcode, unsigned char length, unsigned char *data, bool hasmask = false);

#endif