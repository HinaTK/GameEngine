
#ifndef INNER_PROTO_H
#define INNER_PROTO_H

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
}

#endif // !INNER_PROTO_H
