/*****************************************************************************
*
* File:  winmain.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 10, 2004
*
******************************************************************************
* Desc:  Win32 application entry point
*****************************************************************************/

// --- system includes --- //
#include "bos.h"
#include <windows.h>
#include <commctrl.h>
//#include <commdlg.h>
//#include <basetsd.h>

// --- internal library includes --- //
#include "log.h"
#include "bosapp.h"
#include "appstate.h"

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Entry point to the program. Initializes everything, and goes into a
//       message-processing loop.
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    #ifdef _DEBUG
    // initialize logging utility and enable logging
    if(!CLog::GetLog().Init())  {
        #ifdef WIN32
        MessageBox(NULL,"ERROR: log could not be initialized","Message",MB_OK);
        #else
        cerr<<"ERROR: log could not be initialized"<<endl;
        #endif
    }
    #endif

  	// Ask the user whether or not they want to run in fullscreen
    bool bFullscreen;
    int iAnswer;
    iAnswer = MessageBox(NULL, "Run in fullscreen?", "Fullscreen?", MB_YESNOCANCEL);
	if ( iAnswer==IDYES )
		bFullscreen=true;
	else if ( iAnswer==IDNO )
		bFullscreen=false;
    else
        return 0;

    // create a singleton instance of the application
    new CBOSApplication( TEXT( "Super Street Racer" ), hInst, 640, 480, bFullscreen );

    // init common windows input control classes
    InitCommonControls();  

    // hide the windows mouse cursor
	#ifdef _DEBUG
    ShowCursor(FALSE);     
    #else
    ShowCursor(TRUE);     
	#endif

    // Initialize any pre-game objects
    CAppStateManager::GetAppMan().SetAppState(STATE_INIT);

	// Gib's modification (temporary: begin game in GAME_FRONT_END state)
	CAppStateManager::GetAppMan().SetAppState(STATE_FRONT_END);

    //$$$DEBUG JUMP STRAIGHT IN
    //CAppStateManager::GetAppMan().SetAppState(STATE_IN_GAME);
    // jump into the game loop
    CBOSApplication::GetBOSApp().Run();
        
    // Cleanup any post-game objects
    CAppStateManager::GetAppMan().SetAppState(STATE_CLEAN_UP);

    // destroy the application
    delete CBOSApplication::GetBOSAppPtr();

    // shutdown logging utility
    CLog::GetLog().Shutdown();

    return 0;
}

//END winmain.cpp ==============================================================