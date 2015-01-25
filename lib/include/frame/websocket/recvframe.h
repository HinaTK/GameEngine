
#ifndef RECV_FRAME_H
#define RECV_FRAME_H

#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

class RecvFrame
{
public:
	RecvFrame(NetID _net_id, char *frame);
	~RecvFrame();

	void *			operator new(size_t c);
	void			operator delete(void *m);

	NetID net_id;
	MemoryVL::MemoryInfo data_frame;
};


#endif