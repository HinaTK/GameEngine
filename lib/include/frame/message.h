
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
		data = (char *)MemoryVL::Instance().Malloc(length);
		if (data == NULL)
		{
			data = new char[length];
		}
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
	char *			data;
	//MemoryVL::MemoryInfo data;
};

#endif