
#ifndef INNER_PROTO_H
#define INNER_PROTO_H

#include "innermsgid.h"

#define BindProto(STRUCT, ID)\
	STRUCT() :router(ID){}\
	unsigned short router;

namespace Inner
{
	// game to gateway

	// gateway�յ�����Э��,����㲥��������
	struct ggwBroadcast
	{
		int length;				// ��Ϣ����
		char *data;				// ��Ϣ
	}; 

	// �㲥��ָ������
	struct ggwBroadcastSome
	{
		int some;				// ����
		int *handles;			// ���
		int length;				// ��Ϣ����
		char *data;				// ��Ϣ
	};


	enum ServerType
	{
		ST_GAME = 0,
		ST_GATE,
		ST_MAX
	};

	// ע�����
	struct tocRegisterServer
	{
		BindProto(tocRegisterServer, TOC_REGISTER_SERVER);
		// type + id ����ÿ�������Ψһ��ʶ
		unsigned short type;	// ��������
		unsigned short id;		// ����id
		char ip[32];
		unsigned short port;
	};

	// �㲥��������ע��
	struct ctoBrocastRegister
	{
		BindProto(ctoBrocastRegister, CTO_BROCAST_REGISTER);
		unsigned short type;	// ��������
		unsigned short id;		// ����id
		char ip[32];
		unsigned short port;
	};
}

#endif // !INNER_PROTO_H
