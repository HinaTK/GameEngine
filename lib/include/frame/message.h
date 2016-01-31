
#ifndef MESSAGE_H
#define MESSAGE_H

#include "common/socketdef.h"

// 网络消息
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


class ThreadMsg
{
public:
	ThreadMsg(unsigned char _id, int _length, const char *_data);
	~ThreadMsg();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	unsigned char id;
	int		length;
	char	*data;
};

#endif