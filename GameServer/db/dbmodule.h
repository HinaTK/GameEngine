
#ifndef DB_MODULE_H
#define DB_MODULE_H

class DBThread;
class DBModule
{
public:
	virtual void Exe(DBThread *t) = 0;
};

#endif