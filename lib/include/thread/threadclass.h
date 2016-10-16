
#ifndef THREAD_CLASS_H
#define THREAD_CLASS_H

/*
	将继承函数写到目标线程，发送线程只做new
*/

class BaseThread;
class ThreadClass
{
public:
	virtual void Exe(BaseThread *t) = 0;
};

#endif