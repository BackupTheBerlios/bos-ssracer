/*****************************************************************************
*
* File:  timer.h
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 18, 2004
*
******************************************************************************
* Desc:  Variable Timer task using direct X utilities
*****************************************************************************/
#ifndef TIMER_H
#define TIMER_H

// --- internal library includes --- //
#include "task.h"

//-----------------------------------------------------------------------------
// Class:  CTimer
//
// Desc:  Variable resolution timer to drive the game.
// Runs as a task in the kernel and updates the current time only in Update.
// Default timestep is 10 (1/10th every update) but can be scaled to allow
// provide more stability in the physics engine or slow/fast motion in game.
// Uses modified DX timer commands to get time values
//       
//-----------------------------------------------------------------------------
class CTimer : public ITask
{
public:
	
    CTimer( int xTimeStep );
	virtual ~CTimer();

    static CTimer * GetTimerPtr();  // return pointer
    static CTimer & GetTimer();  // return static reference to singleton
    
	bool Start();
	void Update();
	void Stop();
	void Reset();

    inline void SetTimeStep( int iNewTimeStep ) { m_xTimeStep = iNewTimeStep; };
    inline int GetTimeStep() { return m_xTimeStep; };
    inline float GetTimeElapsed() { return m_fElapsedTime; };
    inline float GetCurrTime() { return m_fCurrTime; };

    // static time conversion functions
    //$$$DEBUG, not sure if we actually need these -JJ
	static inline unsigned long CTimer::TimeToIndex(float fTime) { return (unsigned long)(fTime*1000.0f); }
	static inline float CTimer::IndexToTime(unsigned long lIndex) { return ((float)lIndex)/1000.0f;	      }

protected:
    CTimer();
private:
    static CTimer ms_Timer; // static ref to this singleton
    static float   m_fCurrTime;            // Current time in seconds
    static float   m_fElapsedTime;         // Time elapsed since last frame
    static int     m_xTimeStep;            // Step size for timer each update (1/x)

};



#endif // ifndef TIMER_H
//END timer.h =================================================================
