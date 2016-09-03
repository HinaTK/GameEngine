
#ifndef CENTER_GLOBAL_H
#define CENTER_GLOBAL_H


#include "lib/include/thread/basethread.h"


class ThreadManager;
class Global : public BaseThread
{
public:
	virtual ~Global();
	Global(ThreadManager *manager);


protected:
	bool	Init();
	void	Ready();
	bool	Run();
	void	RecvData(TPT type, ThreadID sid, int len, const char *data);
private:

};

#endif