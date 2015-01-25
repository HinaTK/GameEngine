
#ifndef SEND_FRAME_H
#define SEND_FRAME_H

#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

/*
将一个发送帧写成一个类，这样发送消息队列就只需要保存帧地址即可；
发送完执行回调回收内存
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
