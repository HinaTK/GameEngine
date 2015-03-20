
#ifndef DATA_MAP_MANAGER_H
#define DATA_MAP_MANAGER_H

#include <vector>
#include "lib/include/cache/database.h"

class DataMapManager
{
public:
	
	~DataMapManager(){}

	typedef std::vector<DataBase *> DATA_VECTOR;

	static DataMapManager &Instance()
	{
		static DataMapManager manager;
		return manager;
	}

	void	Init();

	void	RegisterTable(DataBase *data);

	void	Flush();

private:
	DataMapManager();
	DATA_VECTOR	m_data_vector;
};

#endif