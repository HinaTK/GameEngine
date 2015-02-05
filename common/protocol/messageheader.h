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
		MessageHeader(unsigned short type):msg_type(type){}
		unsigned int	msg_type;
	};

	static const int LENGTH = sizeof(MessageHeader);
}

#pragma pack(pop)

#endif