#include "log.h"
#include "soundmessage.h"

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSoundMessage::CSoundMessage() {
	// Set the message type appropriately
	m_nMessageType = SOUND_TASK_MESSAGE;

	// Manually fill with zeroes!
	m_sCommand.nCommandType = NO_COMMAND;
	strcpy( m_sCommand.cSoundName, "" );
	m_sCommand.fVolume = 0.0f;
	m_sCommand.bLooped = false;
	m_sCommand.bIsSound = false;
	m_sCommand.bPause = false;
	m_sCommand.bUnpause = false;
	m_sCommand.bStop = false;
	m_sCommand.bFadeIn = false;
	m_sCommand.fFadeStartPerc = 0;
	m_sCommand.bFadeOut = false;
	m_sCommand.nFadeStep = 0;
	strcpy( m_sCommand.cCrossFade, "" );
}


void CSoundMessage::SetName( char *cNewName ) {
	// Ensure that the new ID isn't too large
	if ( sizeof(cNewName) > MAX_FILENAME_LEN ) return;

	// Copy the new ID across
	strcpy( m_sCommand.cSoundName, cNewName );

	return;
}



void CSoundMessage::PlaySoundEffectOnce( char* cNewName ) {
	m_sCommand.nCommandType = PLAYSOUNDEFFECTONCE_COMMAND;
	CLog::GetLog().Write( LOG_MISC, "***Play sound effect once. %d", m_sCommand.nCommandType );
	SetName( cNewName );
}


void CSoundMessage::PlayMusic( char* cNewName, bool bLooped, float fVolume ) {
	m_sCommand.nCommandType = PLAYMUSIC_COMMAND;
	SetName( cNewName );
	m_sCommand.bLooped = bLooped;
	m_sCommand.fVolume = fVolume;

}


void CSoundMessage::StopMusic() {
	m_sCommand.nCommandType = STOPMUSIC_COMMAND;
}


void CSoundMessage::PlayAmbient( char* cNewName, bool bLooped, float fVolume ) {
	m_sCommand.nCommandType = PLAYAMBIENT_COMMAND;
	SetName( cNewName );
	m_sCommand.bLooped = bLooped;
	m_sCommand.fVolume = fVolume;

}


void CSoundMessage::StopAmbient() {
	m_sCommand.nCommandType = STOPAMBIENT_COMMAND;
}
