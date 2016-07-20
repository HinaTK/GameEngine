
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>

struct ServerInfo
{
	char			ip[16];
	unsigned short	port;
	int				backlog;
};

class ServerConfig
{
public:
	bool	Init();

	ServerInfo center;
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

	bool	Init();

	std::vector<ServerInfo>	m_server;
private:
	GatawayConfig(){};
};

class CenterConfig : public ServerConfig
{
public:
	~CenterConfig(){};
	static CenterConfig &Instance()
	{
		static CenterConfig config;
		return config;
	}

	bool	Init();

	ServerInfo login;
private:
	CenterConfig(){};
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

	bool	Init();

	ServerInfo server;
private:
	GameConfig(){};
};

#endif