/*****************************************************************************
*
* File:  task.h
*
* BurnOut Studios - Super Street Racer
* Module:        Core
* Author:        Jay Javier 
* Modified by:   Rob Diaz-Marino
* Date Created:  Jan 17, 2003
*
******************************************************************************
* Desc:  
*****************************************************************************/
#ifndef TASK_H
#define TASK_H

// Includes
#define STL_USING_ALL
#include "stl.h"
#include <list>

// #defines for Task Types
#define SYSTEM_CALL		-1
#define BASE_TASK		0
#define INPUT_TASK		1
#define RENDER_TASK		2
#define SOUND_TASK		3
#define AI_TASK			4
#define CONSOLE_TASK	5
#define PHYSICS_TASK	6

// #defines for Message Types
#define SYSTEM_TASK_MESSAGE		-1
#define BASE_TASK_MESSAGE		0
#define INPUT_TASK_MESSAGE		1
#define RENDER_TASK_MESSAGE		2
#define SOUND_TASK_MESSAGE		3
#define AI_TASK_MESSAGE			4
#define CONSOLE_TASK_MESSAGE	5
#define PHYSICS_MESSAGE			6

// Forward class definitions
class CKernel;
class ITaskMessage;
class ITask;


class ITaskMessage {
	// Friend classes
	friend class CKernel;

protected:
	float m_fTimeStamp;
	int m_nMessageType;

public:
	ITaskMessage();
	~ITaskMessage() {};

	int GetType() { return m_nMessageType; }
	float GetTimeStamp() { return m_fTimeStamp; }
};


class ITask
{
	// Friend classes
	friend class CKernel;

protected:
	// Protected properties
	std::list< ITaskMessage* > m_lMsgCache;
	CKernel *m_cKernel;
	int m_nTaskType;

	// Protected methods
	virtual void DoMessageHandle( ITaskMessage *cMsg );
	void HandleMessages();

public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest

	// Contructor/Destructor
	ITask();
	~ITask();

	// Overridable methods
    virtual bool Start()=false;
	virtual void OnSuspend(){};
    virtual void Update();
	virtual void OnResume(){};
    virtual void Stop(){};

	// Public methods
	void AddMessage( ITaskMessage *cMsg );
	int GetType() { return m_nTaskType; }

};


#endif