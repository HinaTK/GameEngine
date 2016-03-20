
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>

struct ServerInfo
{
	char			ip[32];
	unsigned short	port;
	int				backlog;
};

class GatawayConfig
{
public:
	~GatawayConfig(){};
	static GatawayConfig &Instance()
	{
		static GatawayConfig config;
		return config;
	}

	bool	Init();

	ServerInfo center;
	std::vector<ServerInfo>	m_server;
private:
	GatawayConfig(){};
};

class CenterConfig
{
public:
	~CenterConfig(){};
	static CenterConfig &Instance()
	{
		static CenterConfig config;
		return config;
	}

	bool	Init();

	ServerInfo center;
	ServerInfo login;
private:
	CenterConfig(){};
};

class GameConfig
{
public:
	~GameConfig(){};
	static GameConfig &Instance()
	{
		static GameConfig config;
		return config;
	}

	bool	Init();

	ServerInfo center;
	ServerInfo server;
private:
	GameConfig(){};
};

#endif