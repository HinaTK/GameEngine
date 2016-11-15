
#include <string>
#include "serverconfig.h"

static const std::string config_file("../config/centerproxy.json");

ServerConfig::ServerConfig()
{
}

bool ServerConfig::Init()
{
	JSON_READ_FILE_BEGIN(config_file.c_str());
	
	JSON_READ_FILE_END(config_file.c_str());
}

bool ServerConfig::ReadServerInfo(char *node, ServerInfo &info)
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

ProxyConfig::ProxyConfig()
{
	if (Init())
	{
		Read();
	}
}

void ProxyConfig::Read()
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
		server.push_back(info);
	}
	
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
	ReadServerInfo("center", server);
}