
#include <string>
#include "serverconfig.h"

static const std::string config_file("../config/server.json");


ServerConfig::ServerConfig()
{
// 	FILE * fp = fopen(config_file.c_str(), "r");
// 	if (fp != NULL){
// 		fseek(fp, 0, SEEK_END);
// 		int file_size = ftell(fp);
// 		if (file_size < 1) {
// 			printf("%s is empty file\n", config_file.c_str());
// 			fclose(fp);
// 			return;
// 		}
// 		char *buf = new char[file_size + 1];
// 		fseek(fp, 0, SEEK_SET);
// 		int read_size = fread(buf, 1, file_size, fp);
// 
// 		if (read_size < 1){
// 			printf("read %s error\n", config_file.c_str());
// 			fclose(fp);
// 			return;
// 		}
// 		buf[read_size] = 0;
// 		fclose(fp);
// 
// 		if (doc.Parse(buf).HasParseError() || !doc.IsObject())
// 		{
// 			delete[] buf;
// 			return;
// 		}
// 		delete[] buf;
// 
// 		if (!doc.HasMember("center") || !doc["center"].IsObject()){
// 			return;
// 		}
// 		rapidjson::Value &object = doc["center"];
// 		if (!object.HasMember("ip") || !object["ip"].IsString())
// 		{
// 			return;
// 		}
// 		rapidjson::Value &ip = object["ip"];
// 
// 		memcpy(center.ip, ip.GetString(), ip.GetStringLength());
// 		if (!object.HasMember("port") || !object["port"].IsInt())
// 		{
// 			return;
// 		}
// 		center.port = object["port"].GetInt();
// 
// 		if (!object.HasMember("backlog") || !object["backlog"].IsInt())
// 		{
// 			return;
// 		}
// 		center.backlog = object["backlog"].GetInt();
// 	}
// 	else {
// 		printf("can not find %s \n", config_file.c_str());
// 		return;
// 	}
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
	if (Init())
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