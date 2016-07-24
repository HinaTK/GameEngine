
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>
#include "lib/include/rapidjson/define.h"

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

	bool	Init();

	ServerInfo center;
protected:
	rapidjson::Document doc;
};

class GatawayConfig : public ServerConfig
{
public:
	~GatawayConfig(){};
	static GatawayConfig &Instance()
	{
		static GatawayConfig config;
		return config;
	}
	void	Read(){}
	bool	Init();

	std::vector<ServerInfo>	m_server;
private:
	GatawayConfig(){};
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

	ServerInfo login;

private:
	CenterConfig();
};

class GameConfig : public ServerConfig
{
public:
	~GameConfig(){};
	static GameConfig &Instance()
	{
		static GameConfig config;
		return config;
	}

	void	Read(){}
	bool	Init();

	ServerInfo server;
private:
	GameConfig(){};
};

#endif