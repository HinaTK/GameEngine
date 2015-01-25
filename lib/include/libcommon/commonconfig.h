
#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <string>
#include <vector>

class CommonConfig
{	
public:
	~CommonConfig();

	static CommonConfig &Instance()
	{
		static CommonConfig config;
		return config;
	}

	
	struct MemoryVL
	{
		unsigned int size;
		unsigned int num;
	};

	typedef std::vector<MemoryVL> MEMORY_VL_VECTOR;
private:
	bool	Init();

public:
	MEMORY_VL_VECTOR &GetMemoryVLVector(){ return m_memory_vl; }
private:
	CommonConfig();
	std::string m_config_file;
	MEMORY_VL_VECTOR	m_memory_vl;
};

#endif