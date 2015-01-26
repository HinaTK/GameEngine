
#ifndef RECV_FRAME_H
#define RECV_FRAME_H

#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

/*
	目前没有使用
*/
class RecvFrame
{
public:
	RecvFrame();
	~RecvFrame();

// 	void *			operator new(size_t c);
// 	void			operator delete(void *m);
// 	MemoryVL::MemoryInfo data_frame;

	bool			CheckHeader(const char *frame);
	bool			Frame(const char *frame);

	char			data[65536];
	unsigned int	length;
};


#endif