
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
		unsigned short buf_len = 0;		// 容器长度
		unsigned short cur_len = 0;		// 数据长度
		unsigned short msg_len = 0;		// 消息总长度
		char *buf = NULL;
	}m_msg;
	Listener *		m_listener;
};


#endif