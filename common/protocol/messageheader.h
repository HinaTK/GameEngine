#ifndef MSGHEADER_H
#define MSGHEADER_H

#include "../../common/commonvariable.h"

#pragma pack(push) 
#pragma pack(4)


namespace IProtocol
{
	enum
	{
		MT_INVALID = 0,
	};
	class MessageHeader
	{
	public:
		MessageHeader(unsigned int type):msg_type(type){}
		unsigned int	msg_type;
	};
	
	static const int LENGTH = sizeof(MessageHeader);
}

namespace EProtocol
{
	enum
	{
		MT_INVALID = 0,
	};

	class MessageHeader
	{
	public:
		MessageHeader(int msg_id) : msgid(msg_id), svrid(-1), check(0), time_s(0){}

		unsigned short		msgid;
		unsigned short		svrid;
		unsigned int		check;
		unsigned int		time_s;
	};

	static const int LENGTH = sizeof(MessageHeader);
}

#pragma pack(pop)

#endif