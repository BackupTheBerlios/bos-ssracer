/*****************************************************************************
*
* File:  timer.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 18, 2003
*
******************************************************************************
* Desc:  Variable Timer task using direct X utilities
*****************************************************************************/

// --- system includes --- //
#include "bos.h"
#include "dxutil.h"

// --- internal library includes --- //
#include "timer.h"
#include "log.h"


float   CTimer::m_fCurrTime = -1.0f;         // Current time in seconds
float   CTimer::m_fElapsedTime = -1;         // Time elapsed since last frame
int     CTimer::m_xTimeStep = 10;            // Step size for timer each update (1/x)

//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CTimer::CTimer()
{
}


CTimer & CTimer::GetTimer()
{
    static CTimer m_Timer;
    return m_Timer;
}


CTimer * CTimer::GetTimerPtr()
{
    return &GetTimer();
}


//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CTimer::CTimer( int xTimeStep )
{
    m_fCurrTime = -1.0f;
    m_fElapsedTime = -1.0f;
    m_xTimeStep = xTimeStep;
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Creating Timer" );
    CLog::GetLog().Write( LOG_MISC, "\tInitial Game Times:  absolute  %f, app  %f, elapsed  %f"
        , DXUtil_Timer( TIMER_GETABSOLUTETIME )
        , DXUtil_Timer( TIMER_GETAPPTIME )
        , DXUtil_Timer( TIMER_GETELAPSEDTIME ) );
    #endif
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
CTimer::~CTimer()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Destroying Timer" );
    #endif
}



//-----------------------------------------------------------------------------
// Name:  Start()
// Desc:  Start the timer
//-----------------------------------------------------------------------------
bool CTimer::Start()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Starting Timer" );
    #endif
	Reset();
	return true;
}



//-----------------------------------------------------------------------------
// Name:  Update()
// Desc:  advance time by 1/x using variable timestep
//-----------------------------------------------------------------------------
void CTimer::Update()
{
    DXUtil_Timer( TIMER_ADVANCE, m_xTimeStep );  ////
    m_fCurrTime = DXUtil_Timer( TIMER_GETAPPTIME );
    m_fElapsedTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );

    #ifdef _DEBUG
    //CLog::GetLog().Write( LOG_GAMECONSOLE, "Current Time: %f Elapsed Time: %f", m_fCurrTime, m_fElapsedTime );
    #endif
}



//-----------------------------------------------------------------------------
// Name:  Reset()
// Desc:  Reset the timer and intitalize system time values 
//-----------------------------------------------------------------------------
void CTimer::Reset()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Resetting Timer" );
    #endif
    DXUtil_Timer( TIMER_RESET );
    DXUtil_Timer( TIMER_START );  // we have to do this or the system times will
    DXUtil_Timer( TIMER_STOP );   // not be initialized properly ////

    m_fCurrTime = DXUtil_Timer( TIMER_GETAPPTIME );
    m_fElapsedTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );
}



//-----------------------------------------------------------------------------
// Name:  Stop()
// Desc:  Pause time
//-----------------------------------------------------------------------------
void CTimer::Stop()
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Stopping Timer" );
    #endif
    DXUtil_Timer( TIMER_STOP );
}



//END timer.cpp ==============================================================
