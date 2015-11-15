
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
		if (!GetSubNodeValue(curElement, "ip", m_server[DATABASE_SERVER].ip, err) ||
			!GetSubNodeValue(curElement, "port", m_server[DATABASE_SERVER].port, err) ||
			!GetSubNodeValue(curElement, "backlog", m_server[DATABASE_SERVER].backlog, err))
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
		if (!GetSubNodeValue(curElement, "ip", m_server[GAME_SERVER].ip, err) ||
			!GetSubNodeValue(curElement, "port", m_server[GAME_SERVER].port, err) ||
			!GetSubNodeValue(curElement, "backlog", m_server[GAME_SERVER].backlog, err))
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
		if (!GetSubNodeValue(curElement, "ip", m_server[LOGIN_SERVER].ip, err) ||
			!GetSubNodeValue(curElement, "port", m_server[LOGIN_SERVER].port, err) ||
			!GetSubNodeValue(curElement, "backlog", m_server[LOGIN_SERVER].backlog, err))
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
		if (!GetSubNodeValue(curElement, "ip", m_server[GATEWAY_SERVER].ip, err) ||
			!GetSubNodeValue(curElement, "port", m_server[GATEWAY_SERVER].port, err) ||
			!GetSubNodeValue(curElement, "backlog", m_server[GATEWAY_SERVER].backlog, err))
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



