
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include "common/systemdef.h"
#include "libcommon/memoryvl.h"

class GameMsg
{
public:
	GameMsg(NetHandle _handle, const char* _data, unsigned int _length)
		: handle(_handle)
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

	NetHandle		handle;
	//NetID			net_id;
	unsigned int	length;
	MemoryVL::MemoryInfo data;
};

#endif