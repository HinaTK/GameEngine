
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string.h>
#include "common/socketdef.h"
#include "lib/include/common/memoryvl.h"

class GameMsg
{
public:
	GameMsg(NetHandle _handle, const char* _data, unsigned int _length);
	~GameMsg();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	NetHandle		handle;
	unsigned int	length;
	char *			data;
};

#endif