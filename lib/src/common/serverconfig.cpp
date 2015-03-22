
#include "serverconfig.h"
#include "libtinyxml.h"

ServerConfig::ServerConfig():
m_config_file("../config/base/serverconfig.xml")
{
	Init();
}

ServerConfig::~ServerConfig()
{

}

void ServerConfig::Init()
{
	ReadDataBaseMysql(m_db_ip, m_db_name, m_user_name, m_password);
	ReadDataBaseSocket();
	ReadGameSocket();
	ReadLoginSocket();
	ReadGatewaySocket();
}

bool ServerConfig::ReadDataBaseMysql( char *ip, char *db_name, char *user_name, char *password )
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("databaseserver");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "databaseserver");
			return false;
		}
		curElement = curElement->FirstChildElement("mysql");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "mysql");
			return false;
		}
		if (!GetSubNodeValue(curElement,	"ip",		ip,			err) ||
			!GetSubNodeValue(curElement,	"dbname",	db_name,	err) ||
			!GetSubNodeValue(curElement,	"username", user_name,	err) ||
			!GetSubNodeValue(curElement,	"password", password,	err))
		{
			ShowError(m_config_file.c_str(), err.c_str());
			return false;
		}

	}
	else
	{
		printf("read database config error\n");
		return false;
	}
	return true;
}

bool ServerConfig::ReadDataBaseSocket()
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("databaseserver");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "databaseserver");
			return false;
		}
		curElement = curElement->FirstChildElement("socket");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "socket");
			return false;
		}
		if (!GetSubNodeValue(curElement, "ip", m_ip[DATABASE_SERVER], err))
		{
			ShowError(m_config_file.c_str(), err.c_str());
			return false;
		}
		TiXmlElement* subElement = curElement->FirstChildElement("listen_game");
		if (subElement == NULL)
		{
			ShowError(m_config_file.c_str(), "listen_game");
			return false;
		}
		if (!GetSubNodeValue(subElement, "port", m_server[DATABASE_GAME].port, err) ||
			!GetSubNodeValue(subElement, "backlog", m_server[DATABASE_GAME].backlog, err))
		{
            ShowError(m_config_file.c_str(), err.c_str());
			return false;
		}
		subElement = curElement->FirstChildElement("listen_login");
		if (subElement == NULL)
		{
            ShowError(m_config_file.c_str(), "listen_login");
			return false;
		}
		if (!GetSubNodeValue(subElement, "port", m_server[DATABASE_LOGIN].port, err) ||
			!GetSubNodeValue(subElement, "backlog", m_server[DATABASE_LOGIN].backlog, err))
		{
			ShowError(m_config_file.c_str(), err.c_str());
			return false;
		}
	}
	else
	{
		printf("can not open config file %s\n",m_config_file.c_str());
		return false;
	}
	return true;
}

bool ServerConfig::ReadGameSocket()
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("gameserver");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "gameserver");
			return false;
		}
		curElement = curElement->FirstChildElement("socket");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "socket");
			return false;
		}
		if (!GetSubNodeValue(curElement, "ip", m_ip[GAME_SERVER], err))
		{
			ShowError(m_config_file.c_str(), "ip");
			return false;
		}
		TiXmlElement* subElement = curElement->FirstChildElement("listen_gateway");
		if (subElement == NULL)
		{
			ShowError(m_config_file.c_str(), "listen_gateway");
			return false;
		}
		if (!GetSubNodeValue(subElement, "port", m_server[GAME_GATEWAY].port, err) ||
			!GetSubNodeValue(subElement, "backlog", m_server[GAME_GATEWAY].backlog, err))
		{
			ShowError(m_config_file.c_str(), "port & backlog");
			return false;
		}
	}
	else
	{
		printf("can not open config file %s\n",m_config_file.c_str());
		return false;
	}
	return true;
}

bool ServerConfig::ReadLoginSocket()
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("loginserver");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "loginserver");
			return false;
		}
		curElement = curElement->FirstChildElement("socket");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "socket");
			return false;
		}
		if (!GetSubNodeValue(curElement, "ip", m_ip[LOGIN_SERVER], err))
		{
			ShowError(m_config_file.c_str(), "ip");
			return false;
		}
		TiXmlElement* subElement = curElement->FirstChildElement("listen_gateway");
		if (subElement == NULL)
		{
			ShowError(m_config_file.c_str(), "listen_gateway");
			return false;
		}
		if (!GetSubNodeValue(subElement, "port", m_server[LOGIN_GATEWAY].port, err) ||
			!GetSubNodeValue(subElement, "backlog", m_server[LOGIN_GATEWAY].backlog, err))
		{
			ShowError(m_config_file.c_str(), "port & backlog");
			return false;
		}
	}
	else
	{
		printf("can not open config file %s\n",m_config_file.c_str());
		return false;
	}
	return true;
}

bool ServerConfig::ReadGatewaySocket( )
{
	std::string err;
	TiXmlDocument doc;
	if (doc.LoadFile(m_config_file.c_str()))
	{
		TiXmlElement* rootElement = doc.RootElement();
		if (rootElement == NULL)
		{
			return false;
		}
		TiXmlElement* curElement = rootElement->FirstChildElement("gatewayserver");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "gatewayserver");
			return false;
		}
		curElement = curElement->FirstChildElement("socket");
		if (curElement == NULL)
		{
			ShowError(m_config_file.c_str(), "socket");
			return false;
		}
		if (!GetSubNodeValue(curElement, "ip", m_ip[GATEWAY_SERVER], err) ||
			!GetSubNodeValue(curElement, "backlog", m_server[GATEWAY_CLIENT].backlog, err) ||
			!GetSubNodeValue(curElement, "port", m_server[GATEWAY_CLIENT].port, err))
		{
			ShowError(m_config_file.c_str(), "ip & backlog & port");
			return false;
		}
	}
	else
	{
		printf("can not open config file %s\n",m_config_file.c_str());
		return false;
	}
	return true;
}



