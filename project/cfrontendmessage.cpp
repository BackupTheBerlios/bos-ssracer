#include "cfrontendmessage.h"

CFrontendMessage::CFrontendMessage(int key)
{
	m_nMessageType = FRONTEND_TASK_MESSAGE;
	m_iKey = key;
}

CFrontendMessage::~CFrontendMessage()
{
	// Nothing to implement here
}