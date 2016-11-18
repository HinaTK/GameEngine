
#ifndef CENTER_PROXY_PROTO_H
#define CENTER_PROXY_PROTO_H

#pragma pack(push)
#pragma pack(4)

namespace InnerProtocol
{
	struct MessageHeader
	{
		MessageHeader(int type) :msgid(type), outer_netid(-1){}

		unsigned short	msgid;
		unsigned short	outer_netid;
	};

	// �����Э��Ҫ��ԭ����һһ��Ӧ
	enum _MsgType
	{
		MT_INTERNAL_INVALID,

		MT_INNER_GATE_SERVER_USER_RECV = 1,
		MT_INNER_SERVER_GATE_USER_SEND_ONE = 4,
		MT_INNER_SERVER_GATE_USER_SEND_MUL,
		MT_INNER_SERVER_GATE_USER_SEND_ALL,
		MT_INNER_SERVER_GATE_USER_DISCONNECT,
		MT_INNER_GAME_TO_CENTER,					// ���س��������ĳ���ͨ��
		MT_INNER_CENTER_TO_GAME,					// ���ĳ����뱾�س���ͨ��
		MT_INNER_CENTER_BACK_TO_GAME,		// ���ķ�������ߣ��ڱ�����������
	};

	struct WGNetRecvMsg
	{
		WGNetRecvMsg() :header(MT_INNER_GATE_SERVER_USER_RECV){}
		MessageHeader	header;
		// �Ӹõ�ַ��ʼΪ�յ���Ϣ������
	};

	struct GWSceneSend
	{
		GWSceneSend() :header(MT_INNER_GAME_TO_CENTER){}
		MessageHeader	header;
		// �����������Ϣ����
	};
}

#pragma pack(pop)

#endif // !CENTER_PROXY_PROTO_H
