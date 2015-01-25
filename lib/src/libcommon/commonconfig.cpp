
#include "commonconfig.h"
#include "libtinyxml.h"

CommonConfig::CommonConfig()
: m_config_file("../config/base/commonconfig.xml")
{
	Init();
}

CommonConfig::~CommonConfig()
{
}

bool CommonConfig::Init()
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("memory_vl");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "memory_vl");
			return false;
		}
		curElement = curElement->FirstChildElement("memory");
		MemoryVL memory;
		while (curElement != NULL)
		{
			if (!GetSubNodeValue(curElement, "size", memory.size, err) ||
				!GetSubNodeValue(curElement, "num",	 memory.num, err))
			{
				ShowError(m_config_file.c_str(), err.c_str());
			}
			m_memory_vl.push_back(memory);
			curElement = curElement->NextSiblingElement();
		}

	}
	else
	{
		printf("read %s config error\n", m_config_file.c_str());
		return false;
	}
	return true;
}
