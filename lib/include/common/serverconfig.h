
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>
#include <string>
#include "lib/include/rapidjson/define.h"

struct ServerInfo
{
	char			ip[16];
	unsigned short	port;
	int				backlog;
};

struct DBInfo
{
	char			ip[16];
	unsigned short	port;
	std::string		user;
	std::string		passwd;
	std::string		dbname;
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

	ServerInfo	login;
	DBInfo		db;

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