#ifndef INPUTTASK_H
#define INPUTTASK_H
/*****************************************************************************
*
* inputtask.h 
*
* BurnOut Studios - Super Street Racer
* Module:  Input
* Author:  Ramit Kar <karr@cpsc.ucalgary.ca>
* Modified by:    On: 
* Date Created:  February 18 2004
*
******************************************************************************
* 
*****************************************************************************/


#include "input.h"
#include "kernel.h"
#include "task.h"
#include "log.h"

class CInputTask : public ITask
{
public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest
	CInput * m_cInput;

	// Public methods
	CInputTask(); 
    bool Start();
    void OnSuspend();
    void Update();
    void OnResume();
    void Stop();
    void DoMessageHandle( ITaskMessage *cMsg ); 
};

#endif