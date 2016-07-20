
#include <string>
#include "serverconfig.h"
#include "lib/include/rapidjson/filereadstream.h"
#include "lib/include/rapidjson/define.h"

static const std::string config_file("../config/server.json");



bool ServerConfig::Init()
{
	JSON_READ_FILE_BEGIN(config_file.c_str());
	rapidjson::Document doc;
	if (doc.Parse(buf).HasParseError() || !doc.IsObject())
	{
		return false;
	}

	if (!doc.HasMember("center") || !doc["center"].IsObject()){
		return false;
	}
	rapidjson::Value &object = doc["center"];
	if (!object.HasMember("ip") || !object["ip"].IsString())
	{
		return false;
	}
	rapidjson::Value &ip = object["ip"];

	memcpy(center.ip, ip.GetString(), ip.GetStringLength());
	if (!object.HasMember("port") || !object["port"].IsInt())
	{
		return false;
	}
	center.port = object["port"].GetInt();

	if (!object.HasMember("backlog") || !object["backlog"].IsInt())
	{
		return false;
	}
	center.backlog = object["backlog"].GetInt();

	JSON_READ_FILE_END(config_file.c_str());
}



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
	FILE * pFile = fopen(config_file.c_str(), "r");
	if (pFile != NULL)
	{
		char buf[1024];
		rapidjson::FileReadStream stream(pFile, buf, 1024);
	}
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
	if (!ServerConfig::Init())
	{
		return false;
	}
	JSON_READ_FILE_BEGIN(config_file.c_str());
	rapidjson::Document doc;
	if (doc.Parse(buf).HasParseError() || !doc.IsObject())
	{
		return false;
	}

	if (!doc.HasMember("login") || !doc["login"].IsObject()){
		return false;
	}
	rapidjson::Value &object = doc["login"];
	if (!object.HasMember("ip") || !object["ip"].IsString())
	{
		return false;
	}
	rapidjson::Value &ip = object["ip"];

	memcpy(login.ip, ip.GetString(), ip.GetStringLength());
	if (!object.HasMember("port") || !object["port"].IsInt())
	{
		return false;
	}
	login.port = object["port"].GetInt();

	if (!object.HasMember("backlog") || !object["backlog"].IsInt())
	{
		return false;
	}
	login.backlog = object["backlog"].GetInt();

	JSON_READ_FILE_END(config_file.c_str());
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