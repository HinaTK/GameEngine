
#include "datamapmanager.h"


DataMapManager::DataMapManager()
{

}

void DataMapManager::Init()
{

}

void DataMapManager::RegisterTable(DataBase * data)
{
	m_data_vector.push_back(data);
}

void DataMapManager::Flush()
{
	DATA_VECTOR::iterator itr = m_data_vector.begin();
	for (DATA_VECTOR::iterator itr = m_data_vector.begin(); itr != m_data_vector.end(); ++itr)
	{
		(*itr)->Flush();
	}
}
