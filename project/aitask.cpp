#include "kernel.h"
#include "aitask.h"
#include "aimessage.h"
#include "inputmessage.h"
#include "soundmessage.h"
#include "consolemessage.h"
// Gib's modification (now receiving frontend messages)
#include "cfrontendmessage.h"
// end Gib's modification
#include "log.h"

#include "gamestatemanager.h"

#include "appstate.h"
#include "input.h"
#include "renderer.h"
#include "macros.h"
//#include "physics.h"

//$$$TEMP
#include "timer.h"


// *************************************************************************** //
// CLASS: CAITask
// *************************************************************************** //

CAITask::CAITask() {
	m_bCanKill=false;
	m_lPriority=5000;

	m_nTaskType = AI_TASK;

}

//---------------------------------------------------------------------------//
// Start()
//---------------------------------------------------------------------------//
bool CAITask::Start() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Starting AI Task..." );
	#endif

	//CScene* scenePtr = new CScene();
	//new CGameStateManager(scenePtr); // no scene to load yet

	if(!CGameStateManager::GetGameStateManagerPtr()) {
		return FALSE;
	}

    m_kInputMap.clear();

	return TRUE;
}




//----------------------------------------------------------------------------
// Stop()
//----------------------------------------------------------------------------
void CAITask::Stop() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_APP, "Stopping AI Task..." );
	#endif

	// Shutdown the game
	CGameStateManager::GetGameStateManagerPtr()->Shutdown();

	m_kInputMap.clear();

	return;
}



//----------------------------------------------------------------------------
// Update()
//----------------------------------------------------------------------------
void CAITask::Update() {

	HandleMessages();

	if (CBOSApplication::GetBOSApp().GetConsoleState() == FALSE)  {
		
		// continue to process any input keys 
		map <int, bool>::iterator it;
		for(it=m_kInputMap.begin(); it!=m_kInputMap.end();it++ ) {

			// generate a input message for any keys still pressed
			if (it->second) {
                // free look camera controls
                if (CRenderer::GetRendererPtr()->GetActiveCameraType() == CAMERA_FREELOOK )
    			    CKernel::GetKernel().DeliverMessage( new CInputTaskMessage(it->first, it->second), RENDER_TASK );
                //else  // driving controls

				// TEMPORARY SHIT FOR PLAYER VEHICLE TESTING
				CGameStateManager::GetGameStateManagerPtr()->ProcessInput( new CInputTaskMessage(it->first, it->second) );
				// #############################################
			}
		}
	}

	return;
}



//----------------------------------------------------------------------------
// DoMessageHandle()
//----------------------------------------------------------------------------
void CAITask::DoMessageHandle( ITaskMessage *cMsg ) {
	CAIMessage *cAIMsg = NULL;

	switch ( cMsg->GetType() ) {

	case INPUT_TASK_MESSAGE:
		HandleInputMessage( (CInputTaskMessage *)cMsg );
		break;


	case AI_TASK_MESSAGE:
		//--------------------------- Handle AI messages here ------//
		cAIMsg = (CAIMessage *) cMsg;
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "AI Task: AI message received with timestamp %f.", cAIMsg->GetTimeStamp() );
		#endif

		//---------------------------------------------------------------//
		break;

	case SYSTEM_TASK_MESSAGE:
		// check for quit message
		break;

	default:
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "AI Task: Message type %d not recognized.", cMsg->GetType() );
		#endif
		break;
	}
}



//---------------------------------------------------------------
// HandleInputMessage
//---------------------------------------------------------------
void CAITask::HandleInputMessage( CInputTaskMessage *cIMsg ) {
	
	#ifdef _DEBUG
	//CLog::GetLog().Write(LOG_MISC, "AI Task: Input message received with timestamp %f.", cIMsg->GetTimeStamp() );
    CLog::GetLog().Write(LOG_MISC, "AI:  cIMsg->m_keyValue %c Hex %x Dec %d", cIMsg->m_keyValue, cIMsg->m_keyValue, cIMsg->m_keyValue );	
	#endif

    switch ( CAppStateManager::GetAppMan().GetAppState() ) {
    
	case STATE_INIT:

	case STATE_CLEAN_UP:
		break;

// Gib's modification (process keyboard input for frontend)
// I put all these cases together 'cause the FEM handles all of them
    case STATE_PAUSE:
	case STATE_POST_GAME:
	case STATE_FRONT_END:

		CFrontendMessage* cFMsg;
		if (cIMsg->m_keyDown) {
			cFMsg = new CFrontendMessage(cIMsg->m_keyValue);
			CKernel::GetKernel().DeliverMessage(cFMsg, FRONTEND_TASK);
		}

		// temporary (to be removed when we've got frontend rendering)
		if (cIMsg->m_keyValue == GAME_ESCAPE)  
			CAppStateManager::GetAppManPtr()->SetAppState(STATE_IN_GAME);
		break;
		// end Gib's modification
	
    case STATE_PRE_GAME:
		// may have special cases here
        //break;

    case STATE_IN_GAME: 
        DEBUGHandleInGameInput( cIMsg );
        break;

    default:        
		break;
	}//end switch
	// END input task handling --------------------------------------//

	
}



void CAITask::DEBUGHandleInGameInput( CInputTaskMessage * cIMsg )
{

    switch ( cIMsg->m_keyValue ) {

	case GAME_ESCAPE:
        //$$$DEBUG  SHOULD SEND A SYSTEM MESSAGE TO GAME AI TELLING IT TO SHUTDOWN
		CKernel::GetKernel().KillAllTasks();  
		break;
	
	// special case for the console
    case '~':
    case '`':
		// see if state has changed
		if ( m_kInputMap[ cIMsg->m_keyValue ] != cIMsg->m_keyDown )  {
			static bool iConsoleOn = false;

			if (iConsoleOn){
				// toggle the console
				CBOSApplication::GetBOSApp().SetConsoleState( FALSE );
				iConsoleOn ^= 1;
				// play a sound
				CKernel::GetKernel().DeliverMessage( new CSoundMessage(), SOUND_TASK );
                m_kInputMap[ cIMsg->m_keyValue ] = FALSE;  // set the key as inactive
			}
			else {
				// toggle the console
				CBOSApplication::GetBOSApp().SetConsoleState( TRUE );
				iConsoleOn ^= 1;
			}

		}
        return;  // don't save the new state
        break;

	default:
		// Check if we need to forward stuff off to the console
		if ( CBOSApplication::GetBOSApp().GetConsoleState() ) {
			// check if the key was just lifted
			if ( m_kInputMap[ cIMsg->m_keyValue ] == cIMsg->m_keyDown ) {
				CKernel::GetKernel().DeliverMessage( new CConsoleMessage( cIMsg->m_keyValue, false, false), CONSOLE_TASK );
			}
            return;  // don't save the new state
		}
        else if (CRenderer::GetRendererPtr()->GetActiveCameraType() == CAMERA_FREELOOK )
       		CKernel::GetKernel().DeliverMessage( new CInputTaskMessage(cIMsg->m_keyValue, cIMsg->m_keyDown), RENDER_TASK );

		// TEMPORARY SHIT FOR PLAYER VEHICLE TESTING
		CGameStateManager::GetGameStateManagerPtr()->ProcessInput( new CInputTaskMessage(cIMsg->m_keyValue, cIMsg->m_keyDown) );
		// #############################################
		break;
    }

    // save the new state of the key
    m_kInputMap[ cIMsg->m_keyValue ] = cIMsg->m_keyDown;
}



/*
//---------------------------------------------------------------
// HandleInputMessage
//---------------------------------------------------------------
void CAITask::HandleInputMessage( CInputTaskMessage *cIMsg ) {

	CSoundMessage *cSMsg = NULL;
	CConsoleMessage *cCMsg = NULL;

	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "AI Task: Input message received with timestamp %f.", cIMsg->GetTimeStamp() );
	#endif
	
	// interpret the incoming keys depending on the application state


	switch(CAppStateManager::GetAppManPtr()->GetAppState())
	{
	case STATE_INIT:
		break;

	case STATE_FRONT_END:
	// input is interpreted by the front end manager
		break;

	case STATE_PRE_GAME:
		break;

	case STATE_IN_GAME:
	// console is down mode: keyboard is for entering commands
	// send message to console task saying which key pressed
	CKernel::GetKernel().DeliverMessage( new CConsoleMessage(//key data//, 
															 false, false);,
															 CONSOLE_TASK );

	// console is up:  
	//	   DEBUG control the free look camera


	//     drive the car
	  
		break;

	case STATE_POST_GAME:
		break;

	case STATE_CLEAN_UP:
		break;

	case STATE_PAUSE:
	// escape key:  change to front end
	
	// special case:  pause key pressed
	//		pause game and rotate camera around player
 
		break;

	default:
		break;
	}  //end switch appstate

}

*/



void CAITask::OnResume() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "AI Task Resumed." );
	#endif
	return;
}



void CAITask::OnSuspend() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "AI Task Suspended." );
	#endif
	return;
}
