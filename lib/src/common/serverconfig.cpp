
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
	info.user = object["user"].GetString();

	if (!object.HasMember("passwd") || !object["passwd"].IsString())
	{
		return false;
	}
	info.passwd = object["passwd"].GetString();

	if (!object.HasMember("dbname") || !object["dbname"].IsString())
	{
		return false;
	}
	info.dbname = object["dbname"].GetString();
	return true;
}

ServerConfig::ServerConfig()
{
}

bool ServerConfig::Init()
{
	JSON_READ_FILE_BEGIN(config_file.c_str());

	if (!doc.HasMember("server") || !doc["server"].IsInt()){
		return false;
	}
	sid = doc["server"].GetInt();

	if (!ReadServerInfo("center", center))
	{
		return false;
	}
	
	JSON_READ_FILE_END(config_file.c_str());
}

bool ReadServerInfo(char *node, ServerInfo &info)
{
	if (!doc.HasMember(node) || !doc[node].IsObject()){
		return false;
	}
	rapidjson::Value &object = doc[node];
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

	if (!object.HasMember("backlog") || !object["backlog"].IsInt())
	{
		return false;
	}
	info.backlog = object["backlog"].GetInt();
	return true;
}

GatawayConfig::GatawayConfig()
{
	if (Init())
	{
		Read();
	}
}

void GatawayConfig::Read()
{
	if (!doc.HasMember("gateway") || !doc["gateway"].IsArray()){
		return;
	}
	ServerInfo info;
	rapidjson::Value &array = doc["gateway"];
	for (unsigned int i = 0; i < array.Size(); ++i)
	{
		rapidjson::Value &object = array[i];
		if (!object.HasMember("ip") || !object["ip"].IsString())
		{
			return;
		}
		rapidjson::Value &ip = object["ip"];

		memcpy(info.ip, ip.GetString(), ip.GetStringLength());
		info.ip[ip.GetStringLength()] = 0;
		if (!object.HasMember("port") || !object["port"].IsInt())
		{
			return;
		}
		info.port = object["port"].GetInt();

		if (!object.HasMember("backlog") || !object["backlog"].IsInt())
		{
			return;
		}
		info.backlog = object["backlog"].GetInt();
		m_server.push_back(info);
	}
	
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
	ReadServerInfo("login", login);
}

GameConfig::GameConfig()
{
	if (Init())
	{
		Read();
	}
}

void GameConfig::Read()
{
	ReadServerInfo("game", game);
}

ProxyConfig::ProxyConfig()
{
	if (Init())
	{
		Read();
	}
}

void ProxyConfig::Read()
{
	ReadServerInfo("proxy", proxy);
}