/***************************************************************************
*
*inputmessage.cpp
*
*BurnOut Studios - Super Street Racer
*Module: Input
*Author: Ramit Kar <karr@cpsc.ucalgary.ca>
*Modified by:
*Date Created: March 2 2004
****************************************************************************
*
****************************************************************************/
#include "inputmessage.h"


//******************************************************************************8
//CInputTaskMessage Class
//This here bad boy is the code for CInputTaskMessage
//
//*******************************************************************************

//Constructor
CInputTaskMessage::CInputTaskMessage()
{
  m_nMessageType = INPUT_TASK_MESSAGE;
  m_keyValue = 0x00;
}

//Overload Constructor that sets all values quickly
CInputTaskMessage::CInputTaskMessage(int keyVal, bool keyDown)
{
  m_nMessageType = INPUT_TASK_MESSAGE;
  m_keyValue = keyVal;
  m_keyDown = keyDown;
}