
#ifndef DATA_MAP_MANAGER_H
#define DATA_MAP_MANAGER_H

#include <vector>
#include "lib/include/cache/cachebase.h"

class DataMapManager
{
public:
	
	~DataMapManager(){}

	typedef std::vector<CacheBase *> DATA_VECTOR;

	static DataMapManager &Instance()
	{
		static DataMapManager manager;
		return manager;
	}

	void	Init();

	void	RegisterTable(CacheBase *data);

	void	Flush();

private:
	DataMapManager();
	DATA_VECTOR	m_data_vector;
};

#endif