
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"
/*
	�����ߣ��������е���������
*/

class Accepter : public NetHandler
{
public:
	Accepter(NetManager *manager, int type, unsigned long _ip) 
		: NetHandler(manager, type)
		, ip(_ip)
	{}
	~Accepter(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);

	unsigned long ip;
private:

};

#endif