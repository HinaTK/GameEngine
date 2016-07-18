
#include <string>
#include "serverconfig.h"
//#include "lib/include/tinyxml/tiny.h"

static const std::string config_file("../config/server.xml");


// bool ReadCenter(TiXmlElement* element, ServerInfo &info)
// {
// 	std::string err;
// 	TiXmlElement* curElement = element->FirstChildElement("center");
// 	if (curElement == NULL)
// 	{
// 		ShowError(config_file.c_str(), "login");
// 		return false;
// 	}
// 
// 	if (!GetSubNodeValue(curElement, "ip", info.ip, err) ||
// 		!GetSubNodeValue(curElement, "port", info.port, err) ||
// 		!GetSubNodeValue(curElement, "backlog", info.backlog, err))
// 	{
// 		ShowError(config_file.c_str(), err.c_str());
// 		return false;
// 	}
// 	return true;
// }

bool GatawayConfig::Init()
{
// 	std::string err;
// 	TiXmlDocument doc;
// 	if (doc.LoadFile(config_file.c_str()))
// 	{
// 		TiXmlElement* rootElement = doc.RootElement();
// 		if (rootElement == NULL)
// 		{
// 			return false;
// 		}
// 		TiXmlElement* curElement = rootElement->FirstChildElement("gateway");
// 		if (curElement == NULL)
// 		{
// 			ShowError(config_file.c_str(), "gateway");
// 			return false;
// 		}
// 		curElement = curElement->FirstChildElement("server");
// 		ServerInfo info;
// 		while (curElement != NULL)
// 		{
// 			if (!GetSubNodeValue(curElement, "ip", info.ip, err) ||
// 				!GetSubNodeValue(curElement, "port", info.port, err) ||
// 				!GetSubNodeValue(curElement, "backlog", info.backlog, err))
// 			{
// 				ShowError(config_file.c_str(), err.c_str());
// 				return false;
// 			}
// 
// 			m_server.push_back(info);
// 			curElement = curElement->NextSiblingElement("server");
// 		}
// 		ReadCenter(rootElement, center);
// 	}
// 	else
// 	{
// 		printf("can not open config file %s\n", config_file.c_str());
// 		return false;
// 	}
	return true;
}

bool CenterConfig::Init()
{
// 	std::string err;
// 	TiXmlDocument doc;
// 	if (doc.LoadFile(config_file.c_str()))
// 	{
// 		TiXmlElement* rootElement = doc.RootElement();
// 		if (rootElement == NULL)
// 		{
// 			return false;
// 		}
// 		TiXmlElement* curElement = rootElement->FirstChildElement("login");
// 		if (curElement == NULL)
// 		{
// 			ShowError(config_file.c_str(), "login");
// 			return false;
// 		}
// 		
// 		if (!GetSubNodeValue(curElement, "ip", login.ip, err) ||
// 			!GetSubNodeValue(curElement, "port", login.port, err) ||
// 			!GetSubNodeValue(curElement, "backlog", login.backlog, err))
// 		{
// 			ShowError(config_file.c_str(), err.c_str());
// 			return false;
// 		}
// 		ReadCenter(rootElement, center);
// 	}
// 	else
// 	{
// 		printf("can not open config file %s\n", config_file.c_str());
// 		return false;
// 	}
	return true;
}

bool GameConfig::Init()
{
// 	std::string err;
// 	TiXmlDocument doc;
// 	if (doc.LoadFile(config_file.c_str()))
// 	{
// 		TiXmlElement* rootElement = doc.RootElement();
// 		if (rootElement == NULL)
// 		{
// 			return false;
// 		}
// 		TiXmlElement* curElement = rootElement->FirstChildElement("game");
// 		if (curElement == NULL)
// 		{
// 			ShowError(config_file.c_str(), "game");
// 			return false;
// 		}
// 
// 		if (!GetSubNodeValue(curElement, "ip", server.ip, err) ||
// 			!GetSubNodeValue(curElement, "port", server.port, err) ||
// 			!GetSubNodeValue(curElement, "backlog", server.backlog, err))
// 		{
// 			ShowError(config_file.c_str(), err.c_str());
// 			return false;
// 		}
// 		ReadCenter(rootElement, center);
// 	}
// 	else
// 	{
// 		printf("can not open config file %s\n", config_file.c_str());
// 		return false;
// 	}
	return true;
}