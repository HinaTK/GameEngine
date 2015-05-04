
#ifndef COMMON_CONFIG_H
#define COMMON_CONFIG_H

#include <string>
#include <vector>
#include "memoryvl.h"

class CommonConfig
{	
public:
	~CommonConfig();

	static CommonConfig &Instance()
	{
		static CommonConfig config;
		return config;
	}

private:
	bool	Init();

public:
	MemoryVL::MEMORY_CONFIG &GetMemoryVLVector(){ return m_memory_vl; }
private:
	CommonConfig();
	std::string m_config_file;
	MemoryVL::MEMORY_CONFIG	m_memory_vl;
};

#endif