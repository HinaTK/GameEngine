
#ifndef DATA_FRAME_H
#define DATA_FRAME_H

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
*/
class DataFrame
{
	static const unsigned int MIN_EXTEND_LEN = 0;
	static const unsigned int MID_EXTEND_LEN = 2;
	static const unsigned int MAX_EXTEND_LEN = 8;
	static const unsigned int MASK_LEN = 4;
	static const unsigned int CONTENT_LEN = 2048;
	static const unsigned int HEADER_LEN = 2;
public:
	~DataFrame(){};
	DataFrame();
	DataFrame(const char *msg);
	
	void			Mask();

	void			Frame(const char* src, unsigned int src_len, char* des, unsigned int &des_len, bool mask = false, bool init_data = false);

	const char		*GetContent(){ return m_content; }

	unsigned int	GetContentLen(){ return m_content_len; }



private:
	char			m_extend[MAX_EXTEND_LEN];	// 由上图可知，（Extended payload length）占8个字节
	char			m_mask[MASK_LEN];			// 由上图可知，占4个字节
	char			m_content[CONTENT_LEN];		// 
	unsigned char	m_extend_len;				// 由上图可知，长度不确定,根据payload长度决定
	unsigned char   m_mask_len;					// 由上图可知，长度不确定,根据是否设置MASK为1决定
	unsigned int	m_content_len;				// 
};



#endif