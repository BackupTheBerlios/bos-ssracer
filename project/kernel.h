/*****************************************************************************
*
* File:  kernel.h
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
#ifndef KERNEL_H
#define KERNEL_H

// --- system includes --- //
#define STL_USING_ALL
#include "stl.h"
#include <algorithm>  // not supported by stl script

// --- internal library includes --- //
#include "task.h"


//-----------------------------------------------------------------------------
// Name: class CBOSApplication
// Desc: Application class. The base class (CD3DApplication) provides the 
//       generic functionality needed in all Direct3D samples. CBOSApplication 
//       adds functionality specific to this sample program.
//-----------------------------------------------------------------------------
class CKernel
{
public:
   	static CKernel * GetKernelPtr();
    static CKernel & GetKernel();

    int Execute();

	bool AddTask( ITask *t);
	void SuspendTask( ITask *t);
	void ResumeTask( ITask *t);
	void RemoveTask( ITask *t);
	void KillAllTasks();
	bool DeliverMessage(ITaskMessage *iMsg, int dest);

protected:
    CKernel() {};
    static CKernel ms_Kernel;
	std::list< ITask* > m_TaskList;
	std::list< ITask* > m_PausedTaskList;
};



#endif
//END kernel.h ==============================================================