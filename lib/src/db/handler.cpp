
#include <stdio.h>
#include "handler.h"
#include "lib/include/base/function.h"

MysqlHandler::MysqlHandler(const char *ip, const char *user, const char *password, const char *db, unsigned short port)
: MysqlBase(ip, user, password, db, port)
, m_1_pool(1, 8)
, m_2_pool(2, 2)
, m_4_pool(4, 4)
, m_8_pool(8, 2)
{
	
}

MysqlHandler::~MysqlHandler()
{

}