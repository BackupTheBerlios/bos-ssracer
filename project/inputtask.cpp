/***************************************************************************
*
*inputtask.cpp
*
*BurnOut Studios - Super Street Racer
*Module: Input
*Author: Ramit Kar <karr@cpsc.ucalgary.ca>
*Modified by:
*Date Created: February 18 2004
****************************************************************************
*
****************************************************************************/

#include "inputtask.h"


CInputTask::CInputTask()
{ m_bCanKill=false; 
  m_lPriority=5000;
  m_nTaskType = INPUT_TASK;
}

bool CInputTask::Start()
{
  
  m_cInput = new CInput();

  if(!m_cInput->start())
    {return false;}
	CLog::GetLog().Write(LOG_MISC, "Input Started");

  return true;
}

void CInputTask::Update()
{

  HandleMessages();
  
  m_cInput->update();

}

void CInputTask::OnSuspend()
{
  //do something when suspended

}

void CInputTask::OnResume()
{
  //do something when not suspended
}

void CInputTask::Stop()
{
  m_cInput->release();
}

void CInputTask::DoMessageHandle( ITaskMessage *cMsg ) {
    //TODO Handle application state change
	switch ( cMsg->GetType() ) {
	case INPUT_TASK_MESSAGE:
    break;
	}
}
