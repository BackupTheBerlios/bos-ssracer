#include "soundtask.h"
#include "soundmessage.h"

// *************************************************************************** //
// CLASS: CSoundTask
// *************************************************************************** //

CSoundTask::CSoundTask() {
	m_bCanKill=true;
	m_lPriority=5000;

	m_nTaskType = SOUND_TASK;
	cPlayList = NULL;
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

	// Resume the soundcore if it's suspended
	if ( CSoundCore::GetSoundCore().IsSuspended() ) {
		CSoundCore::GetSoundCore().Resume();
	}

    //$$$NOTE we're still testing stuff out so we need the game to start without any thing like sound playing`
	// Initialize the playlist if needed
	if ( cPlayList == NULL ) {
		cPlayList = new CPlayList();
		//cPlayList->Load("default");
		//cPlayList->Shuffle();
		//cPlayList->Play( 0.8f, true, true );
	}

	return TRUE;
}


void CSoundTask::OnSuspend() {
	CSoundCore::GetSoundCore().Suspend();
	return;
}


void CSoundTask::Update() {
	HandleMessages();
	cPlayList->Update();
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
	map<CSoundID, CSoundEffect*>::iterator it;
	map<CSoundID, CSoundStream*>::iterator it2;
	CSoundID cSID;
	CSoundEffect *cSfx = NULL;
	CSoundStream *cStr = NULL;

	CLog::GetLog().Write( LOG_MISC, "****In handle sound message. %d", cSMsg->nCommandType );

	switch ( cSMsg->nCommandType ) {
	case KILLSOUND_COMMAND:
		sound.clear();
		stream.clear();
		CSoundCore::GetSoundCore().ResetAll();
		break;

	case KILLSOUNDEFFECTS_COMMAND:
		sound.clear();
		CSoundCore::GetSoundCore().ResetSFX();
		break;

	case KILLSOUNDSTREAMS_COMMAND:
		stream.clear();
		CSoundCore::GetSoundCore().ResetStreams();
		break;

	case PLAYLIST_LOAD_COMMAND:
		cPlayList->Clear();
		cPlayList->Load( cSMsg->cSoundName );
		break;

	case PLAYLIST_PLAY_COMMAND:
		cPlayList->Play( cSMsg->fVolume, cSMsg->bLooped, cSMsg->bPause );
		break;

	case PLAYLIST_STOP_COMMAND:
		cPlayList->Stop();
		break;

	case PLAYLIST_PAUSE_COMMAND:
		cPlayList->Pause();
		break;

	case PLAYLIST_UNPAUSE_COMMAND:
		cPlayList->Unpause();
		break;

	case PLAYLIST_NEXT_COMMAND:
		cPlayList->Next();
		break;

	case PLAYLIST_PREV_COMMAND:
		cPlayList->Prev();
		break;

	case LISTAUDIO_COMMAND:
		// List all loaded sound effects
		CLog::GetLog().Write( LOG_GAMECONSOLE, "------ Loaded Sound Effects: ------" );

		it = sound.begin();
		while ( it != sound.end() ) {
			cSID = it->first;
			cSfx = it->second;
			CLog::GetLog().Write ( LOG_GAMECONSOLE, "::%s:: (time: %2.2fs, play: %d, pause: %d, loop: %d, destruct: %d)", cSID.getID(), cSfx->GetTrackTime(), cSfx->IsPlaying(), cSfx->IsPaused(), cSfx->IsLooping(), cSfx->IsDestruct() );
			it++;
		}

		CLog::GetLog().Write( LOG_GAMECONSOLE, "------ Loaded Sound Streams: ------" );

		it2 = stream.begin();
		while ( it2 != stream.end() ) {
			cSID = it2->first;
			cStr = it2->second;
			CLog::GetLog().Write ( LOG_GAMECONSOLE, "::%s:: (time: %2.2fs, play: %d, pause: %d, loop: %d, destruct: %d)", cSID.getID(), cStr->GetTrackTime(), cStr->IsPlaying(), cStr->IsPaused(), cStr->IsLooping(), cStr->IsDestruct() );
			it2++;
		}
		break;

		CLog::GetLog().Write( LOG_GAMECONSOLE, "-----------------------------------" );

	case PLAYSOUNDEFFECTONCE_COMMAND:
		CLog::GetLog().Write( LOG_GAMECONSOLE, "Sound Task: Playing sound \"%s.wav\" once!", cSMsg->cSoundName );
		CSoundCore::GetSoundCore().GetSoundEffect( cSMsg->cSoundName );
		break;

	case LOADSOUNDEFFECT_COMMAND:
		// Check to see if the sound name is already in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's already present.  Display an error and do nothing.
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" already loaded!", cSMsg->cSoundID );

		}
		else {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Loaded sound \"%s.wav\" as \"%s\".", cSMsg->cSoundName, cSMsg->cSoundID );

			// Sound wasn't found, add to the hashmap
			CSoundCore::GetSoundCore().GetSoundEffect( cSMsg->cSoundName, &cSfx );
			if (cSfx != NULL)
				sound.insert( pair<CSoundID, CSoundEffect*>( CSoundID( cSMsg->cSoundID ), cSfx ) );
		}
		break;

	case PLAYSOUNDEFFECT_COMMAND:
		// Check to see if the sound name is in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's there, let's play it
			it->second->Play( cSMsg->bLooped, false );
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case STOPSOUNDEFFECT_COMMAND:
		// Check to see if the sound name is in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's there, let's stop it
			it->second->Stop();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stopped sound \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case PAUSESOUNDEFFECT_COMMAND:
		// Check to see if the sound name is in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's there, let's pause it
			it->second->Pause();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Paused sound \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case UNPAUSESOUNDEFFECT_COMMAND:
		// Check to see if the sound name is in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's there, let's unpause it
			it->second->Unpause();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Unpaused sound \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case RELEASESOUNDEFFECT_COMMAND:
		// Check to see if the sound name is in the map
		it = sound.find( cSMsg->cSoundID );
		if (it != sound.end()) {
			// It's there, let's release it it
			it->second->Release();

			// Erase the entry in the hashmap
			sound.erase( it );

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Released sound \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Sound \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case PLAYSTREAMONCE_COMMAND:
		CLog::GetLog().Write( LOG_GAMECONSOLE, "Sound Task: Playing stream \"%s.wav\" once!", cSMsg->cSoundName );
		CSoundCore::GetSoundCore().GetSoundStream( cSMsg->cSoundName );
		break;

	case LOADSTREAM_COMMAND:
		// Check to see if the sound name is already in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's already present.  Display an error and do nothing.
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" already loaded!", cSMsg->cSoundID );

		}
		else {
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Loaded stream \"%s.wav\" as \"%s\".", cSMsg->cSoundName, cSMsg->cSoundID );

			// Sound wasn't found, add to the hashmap
			CSoundCore::GetSoundCore().GetSoundStream( cSMsg->cSoundName, &cStr );
			if (cStr != NULL)
				stream.insert( pair<CSoundID, CSoundStream*>( CSoundID( cSMsg->cSoundID ), cStr ) );
		}
		break;

	case PLAYSTREAM_COMMAND:
		// Check to see if the sound name is in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's there, let's play it
			it2->second->FadeIn( cSMsg->bLooped, 0.0f, 0.01f );
			//it2->second->Play( cSMsg->bLooped, false );
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case STOPSTREAM_COMMAND:
		// Check to see if the sound name is in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's there, let's stop it
			it2->second->Stop();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stopped stream \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case PAUSESTREAM_COMMAND:
		// Check to see if the sound name is in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's there, let's pause it
			it2->second->Pause();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Paused stream \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case UNPAUSESTREAM_COMMAND:
		// Check to see if the sound name is in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's there, let's unpause it
			it2->second->Unpause();

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Unpaused stream \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

	case RELEASESTREAM_COMMAND:
		// Check to see if the sound name is in the map
		it2 = stream.find( cSMsg->cSoundID );
		if (it2 != stream.end()) {
			// It's there, let's release it it
			it2->second->Release();

			// Erase the entry in the hashmap
			stream.erase( it2 );

#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Released stream \"%s\".", cSMsg->cSoundID );
#endif
		}
		else {
#ifdef _DEBUG
			CLog::GetLog().Write(LOG_GAMECONSOLE, "Stream \"%s\" doesn't exist!", cSMsg->cSoundID );
#endif
		}
		break;

/*
	case PLAYMUSIC_COMMAND:
		if ( music != NULL ) {
			music->Release();
		}

		if ( strcmp( cSMsg->cSoundName, "" ) != 0 ) {
			CSoundCore::GetSoundCore().GetSoundStream( cSMsg->cSoundName, &music );
			//music->SetVolume( cSMsg->fVolume );
			CLog::GetLog().Write( LOG_MISC, "Music volume: %f", cSMsg->fVolume );
			music->SetVolume( 0.8f );
			music->Play( cSMsg->bLooped, false );

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

		if ( strcmp( cSMsg->cSoundName, "" ) != 0 ) {
			CSoundCore::GetSoundCore().GetSoundStream( cSMsg->cSoundName, &ambient );
			//ambient->SetVolume( cSMsg->fVolume );
			ambient->SetVolume( 0.8f );
			ambient->Play( cSMsg->bLooped, false );

		}
		break;

	case STOPAMBIENT_COMMAND:
		if ( ambient != NULL ) {
			ambient->Stop();
			ambient->Release();
		}
*/
	default:
		break;
	}

	return;
}