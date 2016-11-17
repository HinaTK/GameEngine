
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
		MT_INNER_SCENE_TO_PROXY_TO_SCENE = 9,		// ���س��������ĳ���ͨ��
		MT_INNER_CENTER_TO_GATE = 9
	};

	struct WGNetRecvMsg
	{
		WGNetRecvMsg() :header(MT_INNER_GATE_SERVER_USER_RECV){}
		MessageHeader	header;
		// �Ӹõ�ַ��ʼΪ�յ���Ϣ������
	};

	struct GWSceneSend
	{
		GWSceneSend():header(MT_INNER_SCENE_TO_PROXY_TO_SCENE){}
		MessageHeader	header;
		// �����������Ϣ����
	};

	struct GWGateSend
	{
		GWGateSend():header(MT_INNER_GATE_TO_PROXY_TO_SCENE){}
		MessageHeader	header;
		// �����������Ϣ����
	};
}

#pragma pack(pop)

#endif // !CENTER_PROXY_PROTO_H
