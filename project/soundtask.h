//---------------------------------------------------------------------------//
// File    : soundtask.h
// Author  : Rob Diaz-Marino
// Written : Mar 2004
//---------------------------------------------------------------------------//
#ifndef SOUNDTASK_H
#define SOUNDTASK_H

// STL crap
#define STL_USING_ALL
#include "stl.h"
#include <map>

#include "soundcore.h"
#include "bosapp.h"
#include "soundmessage.h"

class CSoundTask : public ITask
{
public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest
	map<CSoundID, CSoundEffect*> sound;
	map<CSoundID, CSoundStream*> stream;

	// Public methods
	CSoundTask();
    bool Start();
    void OnSuspend();
    void Update();
    void OnResume();
    void Stop();

private:
	// Private members
	void DoMessageHandle( ITaskMessage *cMsg );
	void HandleSoundMessage( CSoundMessage *cSMsg );
};


#endif