/*****************************************************************************
*
* File:  kernel.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 10, 2003
*
******************************************************************************
* Desc:  executes all tasks in the task pool
*****************************************************************************/
#include "log.h"
#include "kernel.h"
#include "timer.h"


CKernel & CKernel::GetKernel()
{
  static CKernel m_Kernel;  // instantiate this singleton class on first use
//  assert (this.m_Log);
  return  m_Kernel;
}

CKernel * CKernel::GetKernelPtr()
{
  return &GetKernel();
}


bool CKernel::DeliverMessage(ITaskMessage *iMsg, int dest) {
	list< ITask* >::iterator i = NULL;

	// Mark the message with the current timestamp.
	// **NOTE** We are assuming that the first task in the list is the timer!!
	iMsg->m_fTimeStamp = ((CTimer*) (*m_TaskList.begin()))->GetCurrTime();

	// Deliver to active messages
	i = m_TaskList.begin();
	while(i != m_TaskList.end()) {

		// See if this is the destination task
		if ( (*i)->GetType() == dest ) {

			// Deliver the message
			(*i)->AddMessage( iMsg );
			CLog::GetLog().Write(LOG_MISC, "Message Delivered!" );
			return true;

		}

		// Move on to the next task
		i++;
	}

	// Deliver to inactive messages
	i = m_PausedTaskList.begin();
	while(i != m_PausedTaskList.end()) {

		// See if this is the destination task
		if ( (*i)->GetType() == dest ) {

			// Deliver the message
			(*i)->AddMessage( iMsg );
			CLog::GetLog().Write(LOG_MISC, "Message Delivered!" );
			return true;

		}

		// Move on to the next task
		i++;
	}

#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Could not deliver message: Destination not found!" );
#endif

	// The message was not delivered because the destination task wasn't found.
	// We must handle deleting the message right here to prevent a memory leak.
	if ( iMsg != NULL ) delete iMsg;

	return false;
}


//-----------------------------------------------------------------------------
// Name: Execute()
// Desc: "The task loop" carries out all tasks in the system to run the game
//   There are always 4 main system tasks in the pool:
//       Timer
//       Input
//       Sound
//       Render
//   Specialized game specific tasks can be added to the pool if needed
//-----------------------------------------------------------------------------
int CKernel::Execute()
{

	while(!m_TaskList.empty())
	{
		{
			std::list< ITask* >::iterator it, thisIt;
			for(it=m_TaskList.begin();it!=m_TaskList.end();)
			{
				ITask *t=(*it);
				++it;
				if(!t->m_bCanKill)t->Update();
			}
			//loop again to remove dead tasks
			for(it=m_TaskList.begin();it!=m_TaskList.end();)
			{
				ITask *t=(*it);
				thisIt=it; ++it;
				if(t->m_bCanKill)
				{
					t->Stop();
					m_TaskList.erase(thisIt);
					t=0;
				}
			}
		}
	}

	return 0;
}



bool CKernel::AddTask(ITask *t)
{
	if(!t->Start())return false;

	//keep the order of priorities straight
	std::list< ITask* >::iterator it;
	for(it=m_TaskList.begin();it!=m_TaskList.end();it++)
	{
		ITask *comp=(*it);
		if(comp->m_lPriority>t->m_lPriority)break;
	}
	m_TaskList.insert(it,t);
	return true;
}



void CKernel::SuspendTask( ITask *t)
{
	//check that this task is in our list - we don't want to suspend a task that isn't running
    if(std::find(m_TaskList.begin(),m_TaskList.end(),t)!=m_TaskList.end())
	{
		t->OnSuspend();
		m_TaskList.remove(t);
		m_PausedTaskList.push_back(t);
	}
}



void CKernel::ResumeTask( ITask *t)
{
    if(std::find(m_PausedTaskList.begin(),m_PausedTaskList.end(),t)!=m_PausedTaskList.end())
	{
		t->OnResume();
		m_PausedTaskList.remove(t);
		//keep the order of priorities straight
		std::list< ITask *>::iterator it;
		for(it=m_TaskList.begin();it!=m_TaskList.end();it++)
		{
			ITask *comp=(*it);
			if(comp->m_lPriority>t->m_lPriority)break;
		}
		m_TaskList.insert(it,t);
	}
}



void CKernel::RemoveTask( ITask *t)
{
	//assert(t.isValid() && "Tried to remove a null task.");
	if(std::find(m_TaskList.begin(),m_TaskList.end(),t)!=m_TaskList.end())
	{
		t->m_bCanKill=true;
		return;
	}
	//check the suspended list
	std::list< ITask* >::iterator it;
	if((it=std::find(m_PausedTaskList.begin(),m_PausedTaskList.end(),t))!=m_TaskList.end())
	{
		//kill the task immediately
		t->Stop();
		m_PausedTaskList.erase(it);
		return;
	}

}



void CKernel::KillAllTasks()
{
	for(std::list< ITask* >::iterator it=m_TaskList.begin();it!=m_TaskList.end();it++)
	{
		(*it)->m_bCanKill=true;
	}
	//kill all paused tasks right now
	for(it=m_PausedTaskList.begin();it!=m_PausedTaskList.end();it++)
	{
		(*it)->Stop();
	}
	m_PausedTaskList.clear();
}
