
#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <string>

class ServerConfig
{
public:
	~ServerConfig();
	static ServerConfig &Instance()
	{
		static ServerConfig config;
		return config;
	}

	enum ServerType
	{
		DATABASE_SERVER,
		GAME_SERVER,
		LOGIN_SERVER,
		GATEWAY_SERVER,
		MAX_SERVER_TYPE
	};

	struct ServerInfo
	{
		char			ip[64];
		unsigned short	port;
		int				backlog;
	};


	void Init();

	bool ReadDataBaseSocket();

	bool ReadDataBaseMysql(char *ip, char *db_name, char *user_name, char *password);

	bool ReadGameSocket();

	bool ReadLoginSocket();

	bool ReadGatewaySocket();

public:
	struct ServerInfo	m_server[MAX_SERVER_TYPE];
	char	m_db_ip[64];
	char	m_db_name[64];
	char	m_user_name[64];
	char	m_password[64];

private:
	ServerConfig();
	std::string m_config_file;

};

#endif