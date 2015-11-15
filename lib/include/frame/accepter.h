
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"

/*
	�����ߣ��������е���������
	ע����������ع�����Ϊ�������Ҳ���Ƶ���������ͷ��ڴ�
*/
class Listener;
class Accepter : public NetHandler
{
public:
	Accepter(NetManager *manager, MsgCallBack *call_back, int type = NetHandler::ACCEPTER)
		: NetHandler(manager, type, new AcceptMsg(call_back))
	{

	}
	~Accepter(){};

	virtual void	OnCanRead();
};

#endif