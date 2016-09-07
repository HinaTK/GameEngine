
#ifndef GATE_BUFFER_H
#define GATE_BUFFER_H

#include "lib/include/base/netcommon.h"

class Listener;
class GateBuffer
{
public:
	GateBuffer(Listener *listener);
	~GateBuffer();

	bool		GetBufInfo(char **buf, int &len);
	int			AddBufLen(int len);

protected:
	void		ResetBuf();
private:
	struct GateMsg
	{
		char *buf = NULL;
		unsigned short buf_len = 0;		// ��������
		unsigned short cur_len = 0;		// ���ݳ���
		unsigned short msg_len = 0;		// ��Ϣ�ܳ���
	}m_msg;
	Listener *		m_listener;
};


#endif