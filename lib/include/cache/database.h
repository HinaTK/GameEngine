
#ifndef DATA_BASE_H
#define DATA_BASE_H

class DataCallBack
{
public:
	DataCallBack(){}
	~DataCallBack(){}

	virtual void OnCallBack(char *key, int operater, const char *data, unsigned int length) = 0;
};

class CacheBase
{
public:
	CacheBase();
	~CacheBase();

	enum 
	{
		INVALID,
		DB_INSERT,
		DB_DELETE,
		DB_FIND,
		DB_UPDATE
	};
	
	virtual void	Flush(){}

};

#endif