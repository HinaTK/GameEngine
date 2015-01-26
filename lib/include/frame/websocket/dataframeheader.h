
#ifndef DATA_FRAME_HEADER_H
#define DATA_FRAME_HEADER_H


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

// ππ‘Ï÷°Õ∑
void ConstructFrameHeader(bool fin, bool rsv1, bool rsv2, bool rsv3, char opcode, unsigned char length, char *data, bool hasmask = false);

#endif