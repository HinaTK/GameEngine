
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
	Accepter(NetManager *manager, int type = NetHandler::ACCEPTER)
		: NetHandler(manager, type)
	{	
	}
	~Accepter(){};

	virtual void	OnCanRead();
	
};

#endif