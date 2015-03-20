
#include "datamapmanager.h"
#include "lib/include/timemanager/gametime.h"
#include "common/globalclass.h"

void *DataFlush(void * arg)
{
	while (DataMapManager::Instance().IsRun())
	{
		DataMapManager::Instance().Flush();
		GameTime::GameSleep(50);
	}
	DataMapManager::Instance().Flush();
	return NULL;
}

DataMapManager::DataMapManager()
: m_is_run(true)
{

}

void DataMapManager::Init()
{
	m_data_thread.Create(DataFlush);
}

void DataMapManager::RegisterTable(CacheBase * data)
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

void DataMapManager::Exit()
{
	m_is_run = false;
}

void DataMapManager::Wait()
{
	m_data_thread.Join();
}
