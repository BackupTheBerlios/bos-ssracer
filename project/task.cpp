//---------------------------------------------------------------------------//
// File    : task.cpp
// Author  : Rob Diaz-Marino
// Modified: Jay Javier
// Written : Feb 2004
//---------------------------------------------------------------------------//

#include "log.h"
#include "task.h"

//===========================================================================//
// CLASS: IMessage
// Desc:
// Overview:
//===========================================================================//
ITaskMessage::ITaskMessage() {
	m_fTimeStamp = 0.0f;
	m_nMessageType = BASE_TASK_MESSAGE;
}


//===========================================================================//
// CLASS: ITask
// Desc:
// Overview:
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
ITask::ITask() {
	m_cKernel = NULL;
	m_nTaskType = BASE_TASK;

	m_bCanKill=false;
	m_lPriority=5000;

	return;
}


//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
ITask::~ITask() {
	m_bCanKill = true;
	m_lPriority = 0;

	// Delete any remaining messages
	list< ITaskMessage* >::iterator it = NULL;
	for (it = m_lMsgCache.begin(); it != m_lMsgCache.end(); it++) {
		if ( (*it) ) delete (*it);
	}

	return;
}

//---------------------------------------------------------------------------//
// NAME: AddMessage
// DESC: Method to add a message to the message cache.
//---------------------------------------------------------------------------//
void ITask::AddMessage(ITaskMessage *cMsg) {
	// Push the message onto the end of the vector.  Messages are only
	// processed upon the call to Update().
	m_lMsgCache.push_back( cMsg );

	CLog::GetLog().Write( LOG_MISC, "Added message.  Total: %d", m_lMsgCache.size() );
	return;
}

//---------------------------------------------------------------------------//
// NAME: HandleMsg
// DESC: Method to be overloaded in child classes that processes a message.
//---------------------------------------------------------------------------//
void ITask::DoMessageHandle(ITaskMessage *cMsg) {
	CLog::GetLog().Write( LOG_MISC, "Handled a message!" );
	return;
}


//---------------------------------------------------------------------------//
// NAME: HandleMessages
// DESC: Iterates through the set of messages that are
//       present in the cache when the function is first called, and forwards
//       the messages to the DoMessageHandle function.
//---------------------------------------------------------------------------//
void ITask::HandleMessages() {
	ITaskMessage *iMsg = NULL;

	// Handle each message in the order it was received (FIFO)
    std::list< ITaskMessage* >::iterator it;
    for (it = m_lMsgCache.begin(); it!=m_lMsgCache.end(); it++)  {
		iMsg = (ITaskMessage*)(*it);

		assert(*it);  // will halt the program if NULL

		//if ( SYSTEM_CALL <= iMsg->GetType() && iMsg->GetType() <= 10 ) {
			// Handle the message
			DoMessageHandle( *it );
			delete *it;  // free the memory pointed to by the iterator NOT the iterator itself -J
		//}

		// Remove the message from the front of the queue
		//m_lMsgCache.pop_front();

        m_lMsgCache.erase(it);

        it = m_lMsgCache.begin();  //reset the iterator because we just popped its object -J
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: Update
// DESC: Method that in most cases should be overridden by child classes.
//       This method is called by the Kernel on a set interval, depending
//       on the task's priority.
//---------------------------------------------------------------------------//
void ITask::Update() {
	HandleMessages();
	return;
}