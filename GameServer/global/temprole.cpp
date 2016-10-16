
#include "temprole.h"

void TempRole::Dispatch(Global *global)
{
	NetMsg msg;
	while (m_msg_queue != NULL && m_msg_queue->Pop(msg)/* && msg != NULL*/)
	{
		Game::Instance().BeforeMessage(global, this, &msg);
	}
}