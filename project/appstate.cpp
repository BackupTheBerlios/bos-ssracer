/*****************************************************************************
*
* File:  appstate.h
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 10, 2003
*
******************************************************************************
* Desc:  Application state manager controls the execution of different parts
*        of the game.
*****************************************************************************/
// --- internal library includes --- //
#include "appstate.h"


//-----------------------------------------------------------------------------
// static member intitialization 
//-----------------------------------------------------------------------------
AppState CAppStateManager::ms_CurrAppState = -1;




bool CAppStateManager::SetApplication( CBOSApplication * pkNewApp )  
{ 
    if ( !pkNewApp )  
        return false;
    else 
        m_pkApp = pkNewApp; 

    return true;
}



CAppStateManager & CAppStateManager::GetAppMan()
{
  static CAppStateManager ms_AppMan;  
  return  ms_AppMan;
}



CAppStateManager * CAppStateManager::GetAppManPtr()
{
  return  &GetAppMan();
}


bool CAppStateManager::Init()
{
    if ( !m_pkApp )  // application pointer must be set first!
        return false;
    else
        SetAppState( STATE_INIT );

    return true;
}



//-----------------------------------------------------------------------------
// Name:  SetAppState()
// Desc:  Sets the current application state and triggers execution of appropriate
//        function in the application
//-----------------------------------------------------------------------------
void CAppStateManager::SetAppState( AppState kNewAppState ) 
{ 
#ifdef _DEBUG
    CLog::GetLog().Write(LOG_APP, (int)kNewAppState, "is being set");
#endif

    // trigger the function in the application
    switch ( kNewAppState )  {
    case STATE_INIT:
        m_pkApp->OnInit();
        break;
    case STATE_FRONT_END:
        m_pkApp->OnFrontEnd();
        break;
    case STATE_PRE_GAME:
        m_pkApp->OnPreGame();
        break;
    case STATE_IN_GAME:
        m_pkApp->OnInGame();
        break;
    case STATE_POST_GAME:
        m_pkApp->OnPostGame();
        break;
    case STATE_CLEAN_UP:
        m_pkApp->OnCleanUp();
        break;
    case STATE_PAUSE:
        m_pkApp->OnPause();
        break;
    default:
#ifdef _DEBUG
    CLog::GetLog().Write(LOG_APP, IDS_APP_ERROR, "Undetermined Application state");
#endif
        //$$$DEBUG do something bad
        break;
    }

    ms_CurrAppState = kNewAppState; 
}


