#ifndef SOUNDTASK_H
#define SOUNDTASK_H

#include "soundcore.h"
#include "bosapp.h"
#include "soundmessage.h"

class CSoundTask : public ITask
{
public:
	// Public properties
	bool m_bCanKill;
	long m_lPriority; // 1 - highest, MAXINT^2 lowest
	CSoundStream *music;
	CSoundStream *ambient;

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