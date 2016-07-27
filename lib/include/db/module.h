
#ifndef DB_MODULE_H
#define DB_MODULE_H

// net thread 发送数据到 db thread都用这个类指针
// 加载的时候调用Load
// 保存的时候调用Save

class DBModule
{
public:
	DBModule(){};
	~DBModule(){};
	
	virtual bool Load(){return false;};
	virtual bool Save(){return false;};
};

#endif
