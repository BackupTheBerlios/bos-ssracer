#ifndef CONSOLETASK_H
#define CONSOLETASK_H

#include "bosapp.h"
#include "task.h"
#include "cinputconsole.h"
#include "ccommandlineparser.h"

class CConsoleTask : public ITask
{
public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest

	// Public methods
	CConsoleTask();
    bool Start();
    void OnSuspend();
    void Update();
    void OnResume();
    void Stop();
	CInputConsole *cIConsole;
	CCommandLineParser *cCLParser;

private:
	// Private members

	void DoMessageHandle( ITaskMessage *cMsg );
};


#endif