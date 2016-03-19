
#include <string>
#include "serverconfig.h"
#include "libtinyxml.h"

static const std::string config_file("../config/server.xml");


bool GatawayConfig::Init()
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("gateway");
		if (curElement == NULL)
		{
			ShowError(config_file.c_str(), "gateway");
			return false;
		}
		curElement = curElement->FirstChildElement("server");
		ServerInfo info;
		while (curElement != NULL)
		{
			if (!GetSubNodeValue(curElement, "ip", info.ip, err) ||
				!GetSubNodeValue(curElement, "port", info.port, err) ||
				!GetSubNodeValue(curElement, "backlog", info.backlog, err))
			{
				ShowError(config_file.c_str(), err.c_str());
				return false;
			}

			m_server.push_back(info);
			curElement = curElement->NextSiblingElement("server");
		}
	}
	else
	{
		printf("can not open config file %s\n", config_file.c_str());
		return false;
	}
	return true;
}
