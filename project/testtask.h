//$$$DEBUG $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//$$$DEBUG USED FOR DEBUGGING PURPOSES ONLY
//$$$DEBUG $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#ifndef TESTTASK_H
#define TESTTASK_H

#include "kernel.h"
#include "task.h"
#include "log.h"

class CTestTask : public ITask
{
public:
	CTestTask(){m_bCanKill=false; m_lPriority=5000;}
    bool Start(){  
#ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, "Starting test task");
#endif
        return true; };
    void OnSuspend(){  
#ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, "Suspending test task");  
#endif
    };
    void Update(){  
        static int xCount = 0;
        //count , then kill everything
        if (xCount++ == 1000)  {
#ifdef _DEBUG
            CLog::GetLog().Write(LOG_APP, "*** Test Task Count is %d Killing all tasks now...", xCount);
#endif
            CKernel::GetKernel().KillAllTasks();
        }
    };
    void OnResume(){  
#ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, "Resuming test task");
#endif    
    };
    void Stop(){  
#ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, "Stopping test task");  
#endif
    };

    bool m_bCanKill;
	long m_lPriority;
};


#endif