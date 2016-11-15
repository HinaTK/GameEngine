
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>
#include <string>
#include "lib/include/rapidjson/define.h"
#include "common/serverdef.h"

struct ServerInfo
{
	char			ip[16];
	unsigned short	port;
	int				backlog;
};

class ServerConfig
{
public:
	ServerConfig();
	~ServerConfig(){}

	bool	ReadServerInfo(char *node, ServerInfo &info);
protected:
	bool	Init();
	rapidjson::Document doc;
};

class ProxyConfig : public ServerConfig
{
public:
	~ProxyConfig(){};
	static ProxyConfig &Instance()
	{
		static ProxyConfig config;
		return config;
	}
	void	Read();

	std::vector<ServerInfo>	server;
private:
	ProxyConfig();
};

class CenterConfig : public ServerConfig
{
public:
	virtual ~CenterConfig(){};
	static CenterConfig &Instance()
	{
		static CenterConfig config;
		return config;
	}

	void	Read();

	ServerInfo	server;

private:
	CenterConfig();
};

#endif