//---------------------------------------------------------------------------//
// File    : aimessage.h
// Author  : Rob Diaz-Marino (stub)
// Written : Feb 2004
//---------------------------------------------------------------------------//

#ifndef _AIMESSAGE_H_
#define _AIMESSAGE_H_

#include "bos.h"
#include "task.h"

// Forward Class Definitions
class CAIMessage;

class CAIMessage : public ITaskMessage
{
public:
	// Public properties

	// Constructor
	CAIMessage();
    CAIMessage( string strR, string strPVName, string strPList );
	~CAIMessage() {};

	// Predefined Actions

    // these are game specific parameters
    string m_strRace;              // sets the map, planes, objects, opponents, starting positions etc.
    string m_strPlayerVehicleName;     
    string m_strPlayList;          // music to play while racing

    // some other stuff might be needed here as well...

protected:
private:

};

#endif