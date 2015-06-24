
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
	GameMsg(NetHandle _handle, int _call_back_handle, const char* _data, unsigned int _length);
	~GameMsg();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	int				call_back_handle;
	NetHandle		handle;
	unsigned int	length;
	char *			data;
};

#endif