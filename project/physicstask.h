#ifndef _PHYSICSTASK_H
#define _PHYSICSTASK_H

#include "kernel.h"
#include "task.h"
#include "log.h"
//#include "physics.h"

class CPhysicsTask : public ITask
{

public:

	// Public methods
	CPhysicsTask();
    bool Start();
    void OnSuspend();
    void Update();
    void OnResume();
    void Stop();
    void DoMessageHandle( ITaskMessage *cMsg );
};

#endif