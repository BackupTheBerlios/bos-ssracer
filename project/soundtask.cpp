#include "soundtask.h"
#include "soundmessage.h"

// *************************************************************************** //
// CLASS: CSoundTask
// *************************************************************************** //

CSoundTask::CSoundTask() {
	m_bCanKill=true;
	m_lPriority=5000;

	m_nTaskType = SOUND_TASK;

	music = NULL;
	ambient = NULL;
}

//---------------------------------------------------------------------------//
// Method to begin the task
//---------------------------------------------------------------------------//
bool CSoundTask::Start() {
	CLog::GetLog().Write(LOG_MISC, "Starting SoundCore Task..." );

	// Attemp to initialize the SoundCore
	if (FAILED( CSoundCore::GetSoundCore().Init(
		CBOSApplication::GetBOSAppPtr()->GetMainWindowHandle(),
		DSSCL_PRIORITY) ))
		return FALSE;

	


	// If the task was stopped, resume now.
	CSoundCore::GetSoundCore().Resume();

	return TRUE;
}


void CSoundTask::OnSuspend() {
	CSoundCore::GetSoundCore().Suspend();
	return;
}


void CSoundTask::Update() {
	HandleMessages();
	return;
}


void CSoundTask::OnResume() {
	CSoundCore::GetSoundCore().Resume();
	return;
}


void CSoundTask::Stop() {
	CLog::GetLog().Write(LOG_APP, "Stopping SoundCore Task..." );

	// First suspend operation
	CSoundCore::GetSoundCore().Suspend();

	return;
}


void CSoundTask::DoMessageHandle( ITaskMessage *cMsg ) {
	switch ( cMsg->GetType() ) {
	case SOUND_TASK_MESSAGE:
		HandleSoundMessage( (CSoundMessage *) cMsg );
		break;
	default:
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_MISC, "Sound Task: Message type %d not recognized.", cMsg->GetType() );
#endif
		break;
	}
}

void CSoundTask::HandleSoundMessage( CSoundMessage *cSMsg ) {
	sSoundCommand sCmd = cSMsg->m_sCommand;

	CLog::GetLog().Write( LOG_MISC, "****In handle sound message. %d", sCmd.nCommandType );

	switch ( sCmd.nCommandType ) {
	case PLAYSOUNDEFFECTONCE_COMMAND:
		// Ensure the Sound Name is specified
		if ( strcmp( sCmd.cSoundName, "" ) != 0 ) {
			CSoundCore::GetSoundCore().GetSoundEffect( sCmd.cSoundName );
		}
		break;

	case PLAYMUSIC_COMMAND:
		if ( music != NULL ) {
			music->Release();
		}

		if ( strcmp( sCmd.cSoundName, "" ) != 0 ) {
			CSoundCore::GetSoundCore().GetSoundStream( sCmd.cSoundName, &music );
			//music->SetVolume( sCmd.fVolume );
			CLog::GetLog().Write( LOG_MISC, "Music volume: %f", sCmd.fVolume );
			music->SetVolume( 0.8f );
			music->Play( sCmd.bLooped, false );

		}
		break;

	case STOPMUSIC_COMMAND:
		if ( music != NULL ) {
			music->Stop();
			music->Release();
		}

	case PLAYAMBIENT_COMMAND:
		if ( ambient != NULL ) {
			ambient->Release();
		}

		if ( strcmp( sCmd.cSoundName, "" ) != 0 ) {
			CSoundCore::GetSoundCore().GetSoundStream( sCmd.cSoundName, &ambient );
			//ambient->SetVolume( sCmd.fVolume );
			ambient->SetVolume( 0.8f );
			ambient->Play( sCmd.bLooped, false );

		}
		break;

	case STOPAMBIENT_COMMAND:
		if ( ambient != NULL ) {
			ambient->Stop();
			ambient->Release();
		}

	default:
		break;
	}

}