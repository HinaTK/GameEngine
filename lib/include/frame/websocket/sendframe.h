
#ifndef SEND_FRAME_H
#define SEND_FRAME_H

#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

/*
��һ������֡д��һ���࣬����������Ϣ���о�ֻ��Ҫ����֡��ַ���ɣ�
������ִ�лص������ڴ�
*/
class SendFrame
{
public:
	SendFrame(NetID _net_id, const char* src, unsigned int src_len, bool mask = false);
	~SendFrame();

	void *			operator new(size_t c);
	void			operator delete(void *m);

	NetID			net_id;
	MemoryVL::MemoryInfo data_frame;
};

#endif
