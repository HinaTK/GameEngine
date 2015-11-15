
#ifndef MESSAGE_H
#define MESSAGE_H

#include "common/socketdef.h"

// class _Msg
// {
// public:
// 	_Msg();
// 	~_Msg();
// 
// 	void *		operator new(size_t c);
// 	void		operator delete(void *m);
// 
// 	NetHandle		handle;
// 	unsigned int	length;
// 	char *			data;
// };

class GameMsg
{
public:
	GameMsg(unsigned short _msg_index, unsigned short _msg_type, NetHandle _handle, const char* _data, unsigned int _length);
	~GameMsg();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	unsigned short	msg_index;
	unsigned short	msg_type;
	NetHandle		handle;
	unsigned int	length;
	char *			data;
};

#endif