/*****************************************************************************
*
* File:  bosapp.cpp
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
// --- system includes --- //
#include "bos.h"

// --- internal library includes --- //
#include "bosapp.h"
#include "appstate.h"
#include "kernel.h"
#include "settings.h"
#include "testtask.h"
#include "timer.h"
#include "aitask.h"
#include "inputtask.h"
#include "soundtask.h"
#include "rendertask.h"
#include "consoletask.h"
#include "physicstask.h"


//-----------------------------------------------------------------------------
// static member intitialization 
//-----------------------------------------------------------------------------
BOOL CBOSApplication::ms_bHasFocus;
HWND CBOSApplication::ms_hWnd                      = NULL;
HINSTANCE CBOSApplication::ms_hInst                = NULL;
TCHAR* CBOSApplication::ms_strWindowTitle          = TEXT( "Default BOS app" );
DWORD CBOSApplication::ms_dwCreationWidth          = 1;
DWORD CBOSApplication::ms_dwCreationHeight         = 1;
BOOL CBOSApplication::ms_bLoadingApp               = FALSE;
CBOSApplication * CBOSApplication::ms_pkBOSApp     = NULL;
RECT CBOSApplication::ms_rcWindow;//                  = (0, 0, 0, 0);
BOOL CBOSApplication::ms_bFullScreen               = FALSE;
BOOL CBOSApplication::ms_bConsoleDown              = FALSE;


//-----------------------------------------------------------------------------
// get functions for the singleton instance of the app
//-----------------------------------------------------------------------------
CBOSApplication & CBOSApplication::GetBOSApp()    {  return *ms_pkBOSApp; }
CBOSApplication * CBOSApplication::GetBOSAppPtr() {  return ms_pkBOSApp;  }



//-----------------------------------------------------------------------------
// Name: CBOSApplication(...)
// Desc: Application constructor.   Paired with ~CBOSApplication()
//       Member variables should be initialized to a known state here.  
//-----------------------------------------------------------------------------
CBOSApplication::CBOSApplication( TCHAR* strWindowTitle, HINSTANCE hInst, DWORD dwWidth, DWORD dwHeight, BOOL bFullScreen )
{
    char chStrTableMsg [256] ;
    LoadString(GetModuleHandle(NULL), IDS_GAME_SETTINGS_FILENAME
                                    ,chStrTableMsg, sizeof(chStrTableMsg));
    // instantiate the game settings manager
    new CSettingsManager( chStrTableMsg );

    ms_pkBOSApp                  = this;
    ms_hInst                     = hInst;
    ms_strWindowTitle            = strWindowTitle;// TEXT( "Super Street Racer" );
    ms_dwCreationWidth           = dwWidth;
    ms_dwCreationHeight          = dwHeight;
    ms_bLoadingApp               = TRUE;
    ms_bFullScreen               = bFullScreen;
    Create( hInst );
}



//-----------------------------------------------------------------------------
// Name: ~CBOSApplication()
// Desc: Application destructor.  Paired with CBOSApplication()
//-----------------------------------------------------------------------------
CBOSApplication::~CBOSApplication()
{
    delete CSettingsManager::GetSettingsManagerPtr();
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Callback for all Windows messages
//-----------------------------------------------------------------------------
LRESULT CBOSApplication::MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        // TODO: Respond to Windows messages as needed

        case WM_COMMAND:
        {
            switch( LOWORD(wParam) )
            {
                case IDM_EXIT:
                    PostQuitMessage( 0 );
                    break;

            }
            break;
        }

        case WM_ACTIVATEAPP:
            ms_bHasFocus = wParam;
            break;

        case WM_ENTERSIZEMOVE:
        case WM_ENTERMENULOOP:
            // Halt frame movement while the app is sizing or moving
            // or when menus are displayed
            Suspend( TRUE );

            break;

        case WM_EXITSIZEMOVE:
        case WM_EXITMENULOOP:
            Suspend( FALSE );
            break;

        case WM_PAINT:
        {
            if( ms_bLoadingApp )
            {
                // Draw on the window tell the user that the app is loading
                // TODO: change as needed
                HDC hDC = GetDC( hWnd );
                TCHAR strMsg[1000];//MAX_PATH];
                wsprintf( strMsg, TEXT("loading game please wait...") );
                RECT rct;
                GetClientRect( hWnd, &rct );
                DrawText( hDC, strMsg, -1, &rct, DT_CENTER|DT_VCENTER);//|DT_SINGLELINE );
                ReleaseDC( hWnd, hDC );
            }
            break;
        }

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}



//-----------------------------------------------------------------------------
// Name: StaticMsgProc()
// Desc: Static msg handler which passes messages to the application class.
//-----------------------------------------------------------------------------
LRESULT CALLBACK StaticMsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    //return g_pApp->MsgProc( hWnd, uMsg, wParam, lParam );
    return CBOSApplication::GetBOSAppPtr()->MsgProc( hWnd, uMsg, wParam, lParam );
}



//-----------------------------------------------------------------------------
// Name: OnPause()
// Desc: Function triggered by Application state manager 
//-----------------------------------------------------------------------------
void CBOSApplication::OnPause() 
{ 
    Suspend (true); //$$$DEBUG for now just suspend the app
    // once tasks are running we set the appstate to STATE_PAUSE and do things like
    // pause the audio playback
    // remap input so only certain keys are available (ie. pause, ~, etc..
    // draw show some cheap pause message 
    
}


//$$$DEBUG windows specific ignore this 
//-----------------------------------------------------------------------------
// Name: Suspend()
// Desc: Called in to toggle the pause state of the app.
//-----------------------------------------------------------------------------
VOID CBOSApplication::Suspend( BOOL bSuspend )
{
    static DWORD dwAppPausedCount = 0L;

    dwAppPausedCount += ( bSuspend ? +1 : -1 );

    // Handle the first pause request (of many, nestable pause requests)
    if( bSuspend && ( 1 == dwAppPausedCount ) )
    {
        // Stop the scene from animating
        //DXUtil_Timer( TIMER_STOP );
        Sleep( 20 );
    }

    if( 0 == dwAppPausedCount )
    {
       // Restart the timers
        //DXUtil_Timer( TIMER_START );
    }
    
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnCleanUp()
{
    if FAILED( FinalCleanup() )  {
          //$$$DEBUG do something bad here
#ifdef _DEBUG
        CLog::GetLog().Write( LOG_APP, IDS_APP_ERROR, "Clean up failed!" );
#endif

    }
}



//-----------------------------------------------------------------------------
// Name: FinalCleanup()
// Desc: Paired with OneTimeInit()
//       Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CBOSApplication::FinalCleanup()
{
    
    // TODO: Perform any final cleanup needed

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: Create()
// Desc: Registers and Creates the window
//-----------------------------------------------------------------------------
HRESULT CBOSApplication::Create( HINSTANCE hInstance )
{
    // set the application state manager to this app
    if (!CAppStateManager::GetAppMan().SetApplication(this) )
        return S_FALSE; 

    // Register the window class
    WNDCLASS wndClass = { CS_DBLCLKS, StaticMsgProc, 0, 0, hInstance, NULL,
                          LoadCursor( NULL, IDC_ARROW ), 
                          (HBRUSH)GetSysColorBrush( COLOR_WINDOW ),
                          NULL, _T("ssracer Class") };

    RegisterClass( &wndClass );

    // Create our main window
    HMENU hMenu = LoadMenu( NULL, MAKEINTRESOURCE(IDR_MENU) );
    ms_hWnd = CreateWindowEx( 0, _T("ssracer Class"), ms_strWindowTitle,
                                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT, 
                                ms_dwCreationWidth, ms_dwCreationHeight, 
                                NULL, hMenu, hInstance, NULL );
        
    if( NULL == ms_hWnd )  {        
        #ifdef _DEBUG
        CLog::GetLog().Write( LOG_APP, IDS_APP_MSG, "Could not create application" );
        #endif
        return E_FAIL;
    }

    // get rectangle for this window
    GetWindowRect( ms_hWnd, &ms_rcWindow );

    
    UpdateWindow( ms_hWnd ); //$$$DEBUG send a paint message to the window

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnInit()
{
    // Get game settings from file
    //$$$DEBUG loads predefined default settings for now
    ReadSettings();

    // Initialize game kernel
    InitializeKernel();

    // Initialize the app's custom scene stuff
    OneTimeInit();
}



//-----------------------------------------------------------------------------
// Name:  ReadSettings
// Desc:  Loads game settings into memory from the settings manager
//-----------------------------------------------------------------------------
void CBOSApplication::ReadSettings()  
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_CORE_MSG, "Loading Game Settings" );
    #endif
    CSettingsManager::GetSettingsManager().LoadDefaultSettings();
}



//-----------------------------------------------------------------------------
// Name:  InitializeKernel()
// Desc:  Initialize kernel with essential tasks
// The highest priority of a task is 1. anything after that is lower.
//-----------------------------------------------------------------------------
void CBOSApplication::InitializeKernel()
{
    // === create system tasks === /
    
/* 
    // Game Timer task
    static CTimer TimerTask(60); // Initialize to 60 clicks per second
    TimerTask.m_lPriority = 10;
    CKernel::GetKernel().AddTask(&TimerTask);

	// AI task
	static CAITask AITask;
	AITask.m_lPriority = 1000;
	CKernel::GetKernel().AddTask(&AITask);

    // input task
    static CInputTask InputTask;  
    InputTask.m_lPriority = 200;
    CKernel::GetKernel().AddTask(&InputTask);

    // sound task
    static CSoundTask SoundTask;  
    SoundTask.m_lPriority = 500;
    CKernel::GetKernel().AddTask(&SoundTask);

	// Physics Task
	static CPhysicsTask PhysicsTask;
	PhysicsTask.m_lPriority = 2000;
	CKernel::GetKernel().AddTask(&PhysicsTask);

    // renderer task
    static CRenderTask RenderTask;  
    RenderTask.m_lPriority = 10000;
    CKernel::GetKernel().AddTask(&RenderTask);

	// Console task
	static CConsoleTask ConsoleTask;
	ConsoleTask.m_lPriority = 100;
	CKernel::GetKernel().AddTask(&ConsoleTask);
*/

    // Game Timer task
    static CTimer TimerTask(200); // Initialize to 60 clicks per second
    TimerTask.m_lPriority = 10;
    CKernel::GetKernel().AddTask(&TimerTask);

    // input task
    static CInputTask InputTask;
    InputTask.m_lPriority = 200;
    CKernel::GetKernel().AddTask(&InputTask);

    // sound task
    static CSoundTask SoundTask;
    SoundTask.m_lPriority = 500;
    CKernel::GetKernel().AddTask(&SoundTask);

   	// Physics Task
	static CPhysicsTask PhysicsTask;
	PhysicsTask.m_lPriority = 2000;
   	CKernel::GetKernel().AddTask(&PhysicsTask);

	// AI task
	static CAITask AITask;
    AITask.m_lPriority = 1000;
    CKernel::GetKernel().AddTask(&AITask);

    // renderer task
    static CRenderTask RenderTask;
    RenderTask.m_lPriority = 10000;
    CKernel::GetKernel().AddTask(&RenderTask);

	// Console task
	static CConsoleTask ConsoleTask;
	ConsoleTask.m_lPriority = 100;
	CKernel::GetKernel().AddTask(&ConsoleTask);


    // test task
    //static CTestTask TTask;  
    //TTask.m_lPriority = 7000;
    //CKernel::GetKernel().AddTask(&TTask);
}



//-----------------------------------------------------------------------------
// Name: OneTimeInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT CBOSApplication::OneTimeInit()
{
    // TODO: perform one time initialization

    // Drawing loading status message until app finishes loading
    SendMessage( ms_hWnd, WM_PAINT, 0, 0 );

    ms_bLoadingApp = FALSE;

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Here's what this function does:
//       - Runs through the message loop.  If no messages are waiting, then
//         it passes control to the game kernel
//       - Messages are forwarded (through WndProc) to CBOSApplication::MsgProc()
//-----------------------------------------------------------------------------
INT CBOSApplication::Run()
{   
	// Load keyboard accelerators for specialized functions (quit, pause, etc)
    HACCEL hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE(IDR_MAIN_ACCEL) );

    // Now we're ready to recieve and process Windows messages.
    //$$$DEBUG    bool bGotMsg;
    MSG  msg;
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
    

	///////////////////////////////////////////////////////////////////////////
	// The "Game Loop" :
	// play the game until user explicitly chooses to quit or the program fails
	///////////////////////////////////////////////////////////////////////////
    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_APP, IDS_APP_MSG, "\t********* Entering the Game Loop *********");
    #endif
    while( WM_QUIT != msg.message  )
    {
        // check any windows specific messages recieved from special key (ex. alt-F4)
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            if( FALSE == GetMessage( &msg, NULL, 0, 0 ) )
                break;

            if( 0 == TranslateAccelerator( ms_hWnd, hAccel, &msg ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
        else
        {
            // execute the kernel task loop
            CKernel::GetKernel().Execute();
            #ifdef _DEBUG
            CLog::GetLog().Write(LOG_APP, IDS_APP_MSG, "Posting Windows Quit Message...");
            #endif  
            // post a quit message to the windows so we can exit the app
            PostQuitMessage( 0 );
        }
    }//END game loop //////////////////////////////////////////////////////////
    #ifdef _DEBUG
    CLog::GetLog().Write(LOG_APP, IDS_APP_MSG, "\t********* Exiting the Game Loop *********");
    #endif

	// cleanup accelerator table
    if( hAccel != NULL )
        DestroyAcceleratorTable( hAccel ); 

    return (INT)msg.wParam;
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnFrontEnd()
{
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnPreGame()
{
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnInGame()
{
}



//-----------------------------------------------------------------------------
// Name: 
// Desc: 
//-----------------------------------------------------------------------------
void CBOSApplication::OnPostGame()
{
}



//END bosapp.cpp ==============================================================
