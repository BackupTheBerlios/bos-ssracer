#include "consolemessage.h"

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CConsoleMessage::CConsoleMessage( int cNewChar, bool bNewReturn, bool bNewBackspace ) {
	// Set the message type appropriately
	m_nMessageType = CONSOLE_TASK_MESSAGE;

	// Set the other properties
	m_cChar = cNewChar;
	m_bReturn = bNewReturn;
	m_bBackspace = bNewBackspace;
}