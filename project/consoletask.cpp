#include "kernel.h"
#include "consoletask.h"
#include "consolemessage.h"
#include "inputmessage.h"
#include "soundmessage.h"
#include "log.h"
#include "macros.h"

// *************************************************************************** //
// CLASS: CAITask
// *************************************************************************** //

CConsoleTask::CConsoleTask() {
	m_bCanKill=false;
	m_lPriority=100;

	m_nTaskType = CONSOLE_TASK;

}

//---------------------------------------------------------------------------//
// Method to begin the task
//---------------------------------------------------------------------------//
bool CConsoleTask::Start() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Starting Console Task..." );
	#endif

	cCLParser = new CCommandLineParser();
	cIConsole = new CInputConsole("\0");

	return TRUE;
}


void CConsoleTask::OnSuspend() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Console Task Suspended." );
	#endif
	return;
}


void CConsoleTask::Update() {
	HandleMessages();
	return;
}


void CConsoleTask::OnResume() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Console Task Resumed." );
	#endif
	return;
}


void CConsoleTask::Stop() {
	#ifdef _DEBUG
	CLog::GetLog().Write(LOG_APP, "Stopping Console Task..." );
	#endif

	delete cCLParser;
	delete cIConsole;

	return;
}


void CConsoleTask::DoMessageHandle( ITaskMessage *cMsg ) {
	CConsoleMessage *cCMsg = NULL;

	switch ( cMsg->GetType() ) {

	case CONSOLE_TASK_MESSAGE:
		cCMsg = (CConsoleMessage *) cMsg;
		#ifdef _DEBUG
		//CLog::GetLog().Write(LOG_MISC, "Console Task: Console message received with timestamp %f.", cCMsg->GetTimeStamp() );
        //CLog::GetLog().Write( LOG_GAMECONSOLE, "Console Task: cCMsg->m_cChar %c Hex %x Dec %d' pressed.", cCMsg->m_cChar, cCMsg->m_cChar, cCMsg->m_cChar );
		#endif
		
		// interpret the character received forwarded from input message
		switch ( cIConsole->evaluateChar( cCMsg->m_cChar ) ) {

		case OK:
			cIConsole->addChar( cCMsg->m_cChar );
			//cIConsole->printBuffer( LOG_GAMECONSOLE );
			break;

		case CONSOLE_TOGGLE:
			cIConsole->clearBuffer();
		//	cIConsole->printBuffer( LOG_GAMECONSOLE );
			break;

		case BACKSPACE:
			cIConsole->deleteChar();
		//	cIConsole->printBuffer( LOG_GAMECONSOLE );
			break;

		// Gib's modification (Sorry Rob, I've gotta do this)
		case UP_ARROW:
			cIConsole->arrowKeyPressed(UP_ARROW);
			break;

		case DOWN_ARROW:
			cIConsole->arrowKeyPressed(DOWN_ARROW);
			break;

		case ENTER:
			if ( cIConsole->processCommand( cCLParser ) != OK ) {
				CLog::GetLog().Write( LOG_GAMECONSOLE, "ERROR: Command not recognized." );
			}
			cIConsole->clearBuffer();
			break;

		default:  //NONPRINTABLE

			break;
		}		//--------------------------------------//
		break;

	default:
		#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "Console Task: Message type %d not recognized.", cMsg->GetType() );
		#endif
		break;
	}
}