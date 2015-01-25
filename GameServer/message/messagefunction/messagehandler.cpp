#include "messagehandler.h"

MessageHandler::MessageHandler()
{
	memset(m_function_list, 0, sizeof(m_function_list));
    m_function_list[REAL_TYPE(EProtocol::MT_MSG_TEST1)] = HandlerItem(&MessageHandler::TestFunction,12);
}


void MessageHandler::TestFunction( Role *role, char *msg )
{

}

