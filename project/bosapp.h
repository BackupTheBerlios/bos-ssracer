/*****************************************************************************
*
* File:  bosapp.h
*
* BurnOut Studios - Super Street Racer
* Module:  Core
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 10, 2003
*
******************************************************************************
* Desc:  DirectX/win32 window application layer
*****************************************************************************/
#ifndef BOSAPP_H
#define BOSAPP_H

// --- system includes --- //
#include "bos.h"
#include <windows.h>
#include <tchar.h>

// --- internal library includes --- //



class CAppStateManager;  // forward declaration


//-----------------------------------------------------------------------------
// Name: class CBOSApplication
// Desc: Application class. 
//-----------------------------------------------------------------------------
class CBOSApplication
{
    friend class CAppStateManager;  // needed to trigger certain functions on state change

    /////////////////////////////// class members /////////////////////////////
private:
    static BOOL                    ms_bLoadingApp;          // TRUE, if the app is loading
    static BOOL              	   ms_bHasFocus;	        // TRUE, if the app has focus
    static TCHAR*                  ms_strWindowTitle;       // Title for the app's window
    static HWND                    ms_hWnd;                 // Handle to the main window
    static HINSTANCE               ms_hInst;                // Instance of the main window
    static DWORD                   ms_dwCreationWidth;      // Width used to create window
    static DWORD                   ms_dwCreationHeight;     // Height used to create window
    static RECT                    ms_rcWindow;             // rectangle describing window
    static BOOL                    ms_bFullScreen;          // TRUE if the app is fullscreen
    static BOOL                    ms_bConsoleDown;         // TRUE if the in game console is displayed
    static BOOL                    ms_bShowDebugOverlay;    // TRUE if debug overlay is to be shown

protected:
    static CBOSApplication * ms_pkBOSApp; // static reference to this singleton


    ////////////////////////////// member functions ///////////////////////////
public:    
    CBOSApplication( TCHAR* strWindowTitle, HINSTANCE hInst, DWORD dwWidth, DWORD dwHeight, BOOL bFullScreen );
    ~CBOSApplication();
    
    // singleton instance get functions
    static CBOSApplication & GetBOSApp();
    static CBOSApplication * GetBOSAppPtr();

    HWND    GetMainWindowHandle(){ return ms_hWnd; };
    HINSTANCE GetMainInstanceHandle(){ return ms_hInst; };

    INT     Run();  // execute the game loop

    LRESULT MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );    
    VOID    Suspend( BOOL bSuspend );  // windows specific function if app is minimized, or lost focus

    BOOL IsFullScreen() { return ms_bFullScreen; };
    void SetFullScreen(bool bFullScreen) { ms_bFullScreen = bFullScreen; };

    DWORD GetWidth() { return ms_dwCreationWidth; };
    DWORD GetHeight() { return ms_dwCreationHeight; };

    BOOL GetConsoleState() { return ms_bConsoleDown; }; 
    void SetConsoleState( bool bNewState ) { ms_bConsoleDown = bNewState; };
    BOOL ToggleConsoleState() { ms_bConsoleDown = !ms_bConsoleDown;  return ms_bConsoleDown; }; 

    BOOL GetDebugOverlayState() { return ms_bShowDebugOverlay; }; 
    void SetDebugOverlayState( bool bNewState ) { ms_bShowDebugOverlay = bNewState; };
    

protected:
    void    InitializeKernel();         // create system and game tasks
    virtual HRESULT OneTimeInit();
    virtual HRESULT FinalCleanup();
    VOID    ReadSettings();
    VOID    WriteSettings();
    HRESULT RenderText();          //$$$DEBUG

private:
    HRESULT Create( HINSTANCE hInstance );  // register and create the app window

    // application state changes will trigger execution of these functions
    VOID    OnInit();
    VOID    OnFrontEnd();
    VOID    OnPreGame();
    VOID    OnInGame();
    VOID    OnPostGame();
    VOID    OnCleanUp();
    VOID    OnPause();
};



#endif
//END bosapp.h ==============================================================
