
#ifndef THREAD_CLASS_H
#define THREAD_CLASS_H

/*
	���̳к���д��Ŀ���̣߳������߳�ֻ��new
*/

class BaseThread;
class ThreadClass
{
public:
	virtual void Exe(BaseThread *t) = 0;
};

#endif