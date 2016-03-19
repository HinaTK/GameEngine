
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <vector>

struct ServerInfo
{
	char			ip[64];
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

	std::vector<ServerInfo>	m_server;
private:
	GatawayConfig(){};
};

#endif