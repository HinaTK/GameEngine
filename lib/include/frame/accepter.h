
#ifndef ACCEPTER_H
#define ACCEPTER_H

#include "nethandler.h"
/*
	�����ߣ��������е���������
*/

class Accepter : public NetHandler
{
public:
	Accepter(NetManager *manager, int type) : NetHandler(manager, type){};
	~Accepter(){};

	virtual void	OnCanRead();

	void *		operator new(size_t c);
	void		operator delete(void *m);
private:

};

#endif