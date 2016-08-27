
#ifndef THREAD_CLASS_H
#define THREAD_CLASS_H

class BaseThread;
class ThreadClass
{
public:
	virtual void Exe(BaseThread *t) = 0;
};

#endif