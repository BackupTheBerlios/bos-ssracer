/*****************************************************************************
*
* File:  appstate.h
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 10, 2004
*
******************************************************************************
* Desc:  Application state manager controls the execution of different parts
*        of the game.
*****************************************************************************/
#ifndef APPSTATE_H
#define APPSTATE_H

// --- internal library includes --- //
#include "bosapp.h"
#include "log.h"

// --- defines and constant declarations --- //
// These are the actual app states the game goes through
// the string table entries in ssracer.rc match the values here
// so the logger can write a predefined message
#define STATE_INIT 7000
#define STATE_FRONT_END 7001
#define STATE_PRE_GAME 7002
#define STATE_IN_GAME 7003
#define STATE_POST_GAME 7004
#define STATE_CLEAN_UP 7005
#define STATE_PAUSE 7006

typedef int AppState;


//-----------------------------------------------------------------------------
// Class:  CAppStateManager
// Desc:  Manages the current application state.  State changes are determined
//        by conditions within the game itself.
//-----------------------------------------------------------------------------
class CAppStateManager 
{
    friend class CBOSApplication;

public:
    bool SetApplication( CBOSApplication * pkNewApp );
    bool Init();
    
    // singleton get functions
    static CAppStateManager & GetAppMan();
    static CAppStateManager * GetAppManPtr();

    void SetAppState( AppState kNewAppState );
    AppState GetAppState() { return ms_CurrAppState; };

protected:
    CAppStateManager(){};
    static CAppStateManager ms_AppMan;  

private:
    static AppState ms_CurrAppState;
    CBOSApplication * m_pkApp; // pointer to the current application this manages
};



#endif
//END appstate.h ==============================================================