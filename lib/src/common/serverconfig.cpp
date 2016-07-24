
#include <string>
#include "serverconfig.h"

static const std::string config_file("../config/server.json");

bool ReadDB(rapidjson::Document &doc, DBInfo &info)
{
	if (!doc.HasMember("db") || !doc["db"].IsObject()){
		return false;
	}
	rapidjson::Value &object = doc["db"];
	if (!object.HasMember("ip") || !object["ip"].IsString())
	{
		return false;
	}
	rapidjson::Value &ip = object["ip"];

	memcpy(info.ip, ip.GetString(), ip.GetStringLength());
	if (!object.HasMember("port") || !object["port"].IsInt())
	{
		return false;
	}
	info.port = object["port"].GetInt();

	if (!object.HasMember("user") || !object["user"].IsString())
	{
		return false;
	}
	info.user = object["GetString"].GetString();

	if (!object.HasMember("passwd") || !object["passwd"].IsString())
	{
		return false;
	}
	info.user = object["passwd"].GetString();

	if (!object.HasMember("dbname") || !object["dbname"].IsString())
	{
		return false;
	}
	info.user = object["dbname"].GetString();
	return true;
}

ServerConfig::ServerConfig()
{
}

bool ServerConfig::Init()
{
	JSON_READ_FILE_BEGIN(config_file.c_str());
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

CenterConfig::CenterConfig()
{
	if (Init() && ReadDB(doc, db))
	{
		Read();
	}
}

void CenterConfig::Read()
{
	if (!doc.HasMember("login") || !doc["login"].IsObject()){
		return;
	}
	rapidjson::Value &object = doc["login"];
	if (!object.HasMember("ip") || !object["ip"].IsString())
	{
		return;
	}
	rapidjson::Value &ip = object["ip"];

	memcpy(login.ip, ip.GetString(), ip.GetStringLength());
	if (!object.HasMember("port") || !object["port"].IsInt())
	{
		return;
	}
	login.port = object["port"].GetInt();

	if (!object.HasMember("backlog") || !object["backlog"].IsInt())
	{
		return;
	}
	login.backlog = object["backlog"].GetInt();
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