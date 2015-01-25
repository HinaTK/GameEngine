
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

	// server->client
	enum InternalType
	{
		DATABASE_GAME,			// 
		DATABASE_LOGIN,
		GAME_GATEWAY,
		LOGIN_GATEWAY,
		GATEWAY_CLIENT,			// 对外的唯一接口
		MAX_INTERNAL_TYPE
	};

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
	typedef char							IP[64];

public:
	struct ServerInfo	m_server[MAX_INTERNAL_TYPE];
	IP					m_ip[MAX_SERVER_TYPE];
	//unsigned short		m_internal[MAX_INTERNAL_TYPE];
	IP		m_db_ip;
	char	m_db_name[64];
	char	m_user_name[64];
	char	m_password[64];

private:
	ServerConfig();
	std::string m_config_file;

};

#endif