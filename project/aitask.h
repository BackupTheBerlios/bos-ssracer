#ifndef AITASK_H
#define AITASK_H

#include "bosapp.h"
#include "task.h"
#include "inputmessage.h"
#include "aimessage.h"

#define STL_USING_MAP
#include "stl.h"

class CAITask : public ITask
{
public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest

	// Public methods
	CAITask();
    bool Start();
    void OnSuspend();
    void Update();
    void OnResume();
    void Stop();

private:	
	void DoMessageHandle( ITaskMessage *cMsg );
	void HandleInputMessage( CInputTaskMessage *cIMsg );
    void HandleAIMessage( CAIMessage *cAIMsg );
    void DEBUGHandleInGameInput( CInputTaskMessage * cIMsg );

	// stores key states from input messages
	std::map< int, bool > m_kInputMap;
};


#endif