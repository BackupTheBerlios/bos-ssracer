//---------------------------------------------------------------------------//
// File    : consolemessage.h
// Author  : Rob Diaz-Marino (stub)
// Written : Feb 2004
//---------------------------------------------------------------------------//

#ifndef _CONSOLEMESSAGE_H_
#define _CONSOLEMESSAGE_H_

#include "bos.h"
#include "task.h"

// Forward Class Definitions
class CConsoleMessage;

class CConsoleMessage : public ITaskMessage
{
public:
	// Public properties
	int m_cChar;
	bool m_bReturn;
	bool m_bBackspace;

	// Constructor
	CConsoleMessage( int cNewChar, bool bNewReturn, bool bNewBackspace );
	~CConsoleMessage() {};

	// Predefined Actions

protected:
private:
};

#endif