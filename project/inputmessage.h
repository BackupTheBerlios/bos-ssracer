#ifndef INPUTMESSAGE_H
#define INPUTMESSAGE_H

#include "task.h"
#include "bos.h"
#include "windows.h"

//-----------------------------------------------------------------------------
// Class:  CInputTaskMessage
//
// Desc:  Msgs from Input task
//-----------------------------------------------------------------------------
class CInputTaskMessage : public ITaskMessage
{
public:
    //Public attributes
    int m_keyValue;
	bool m_keyDown;

    // Public methods
    CInputTaskMessage(); 
    CInputTaskMessage(int keyVal, bool keyDown);

};

#endif