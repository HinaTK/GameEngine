
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

class GameMsg
{
public:
	GameMsg(NetID _net_id, const char* _data, unsigned int _length)
		: net_id(_net_id)
		, length(_length)
	{
		if (!MemoryVL::Instance().Malloc(length, data))
		{
			return;
		}
		memcpy(data.mem, _data, length);
	}
	~GameMsg()
	{
		MemoryVL::Instance().Free(data);
	}

	void *		operator new(size_t c);
	void		operator delete(void *m);

	NetID			net_id;
	unsigned int	length;
	MemoryVL::MemoryInfo data;
};

#endif