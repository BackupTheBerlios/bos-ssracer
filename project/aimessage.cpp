#include "aimessage.h"

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CAIMessage::CAIMessage() {
	// Set the message type appropriately
	m_nMessageType = AI_TASK_MESSAGE;
}

CAIMessage::CAIMessage( string strR, string strPVName, string strPList )
{
    m_nMessageType = AI_TASK_MESSAGE;
    m_strRace = strR;
    m_strPlayerVehicleName = strPVName;
    m_strPlayList = strPList;
};