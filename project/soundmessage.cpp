#include "log.h"
#include "soundmessage.h"

#define STL_USING_STRING
#include "stl.h"


bool operator<(CSoundID a, CSoundID b) {
	return strcmp(a.getID(), b.getID()) < 0;
}

bool operator>(CSoundID a, CSoundID b) {
	return strcmp(a.getID(), b.getID()) > 0;
}


//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSoundMessage::CSoundMessage() {
	// Set the message type appropriately
	m_nMessageType = SOUND_TASK_MESSAGE;

	// Manually fill with zeroes!
	nCommandType = NO_COMMAND;
	strcpy( cSoundID, "" );
	strcpy( cSoundName, "" );
	fVolume = 0.0f;
	bLooped = false;
	bPause = false;
	bUnpause = false;
	bStop = false;
	bFadeIn = false;
	fFadeStartPerc = 0;
	bFadeOut = false;
	nFadeStep = 0;
	strcpy( cCrossFade, "" );

	return;
}


//---------------------------------------------------------------------------//
// SOUND EFFECT COMMANDS
//---------------------------------------------------------------------------//
void CSoundMessage::PlaySoundEffectOnce( std::string sNewName ) {
	if ( sNewName.size() > MAX_FILENAME_LEN ) return;

	// Set command properties
	nCommandType = PLAYSOUNDEFFECTONCE_COMMAND;
	strcpy( cSoundName, sNewName.c_str() );

	return;
}


void CSoundMessage::PlaySoundEffect( std::string sID, bool loop  ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = PLAYSOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sID.c_str() );
	bLooped = loop;

	return;
}


void CSoundMessage::LoadSoundEffect( std::string sNewName, std::string sNewID ) {
	if ( sNewID.size() > MAX_ID_LEN ) return;
	if ( sNewName.size() > MAX_FILENAME_LEN ) return;

	// Set command properties
	nCommandType = LOADSOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sNewID.c_str() );
	strcpy( cSoundName, sNewName.c_str() );

	return;
}


void CSoundMessage::StopSoundEffect( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = STOPSOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::PauseSoundEffect( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = PAUSESOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::UnpauseSoundEffect( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = UNPAUSESOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::ReleaseSoundEffect( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = RELEASESOUNDEFFECT_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


//---------------------------------------------------------------------------//
// STREAM COMMANDS
//---------------------------------------------------------------------------//
void CSoundMessage::PlayStreamOnce( std::string sNewName ) {
	if ( sNewName.size() > MAX_FILENAME_LEN ) return;

	// Set command properties
	nCommandType = PLAYSTREAMONCE_COMMAND;
	strcpy( cSoundName, sNewName.c_str() );

	return;
}


void CSoundMessage::PlayStream( std::string sID, bool loop  ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = PLAYSTREAM_COMMAND;
	strcpy( cSoundID, sID.c_str() );
	bLooped = loop;

	return;
}


void CSoundMessage::LoadStream( std::string sNewName, std::string sNewID ) {
	if ( sNewID.size() > MAX_ID_LEN ) return;
	if ( sNewName.size() > MAX_FILENAME_LEN ) return;

	// Set command properties
	nCommandType = LOADSTREAM_COMMAND;
	strcpy( cSoundID, sNewID.c_str() );
	strcpy( cSoundName, sNewName.c_str() );

	return;
}


void CSoundMessage::StopStream( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = STOPSTREAM_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::PauseStream( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = PAUSESTREAM_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::UnpauseStream( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = UNPAUSESTREAM_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


void CSoundMessage::ReleaseStream( std::string sID ) {
	if ( sID.size() > MAX_ID_LEN ) return;

	// Set command properties
	nCommandType = RELEASESTREAM_COMMAND;
	strcpy( cSoundID, sID.c_str() );

	return;
}


//---------------------------------------------------------------------------//
// PLAYLIST COMMANDS
//---------------------------------------------------------------------------//
void CSoundMessage::LoadList( std::string sListFile ) {
	if ( sListFile.size() > MAX_FILENAME_LEN ) return;

	// Set command properties
	nCommandType = PLAYLIST_LOAD_COMMAND
	strcpy( cSoundName, sListFile.c_str() );

	return;
}


void CSoundMessage::PlayList( float fNewVolume, bool bAutoRepeat, bool bAutoAdvance ) {
	// Set command properties
	nCommandType = PLAYLIST_PLAY_COMMAND
	fVolume = fNewVolume;
	bLooped = bAutoRepeat;
	bPause = bAutoAdvance;

	return;
}


void CSoundMessage::StopList() {
	// Set command properties
	nCommandType = PLAYLIST_STOP_COMMAND

	return;
}


void CSoundMessage::PauseList() {
	// Set command properties
	nCommandType = PLAYLIST_PAUSE_COMMAND

	return;
}


void CSoundMessage::UnpauseList() {
	// Set command properties
	nCommandType = PLAYLIST_UNPAUSE_COMMAND

	return;
}


//---------------------------------------------------------------------------//
// SOUNDCORE COMMANDS
//---------------------------------------------------------------------------//
void CSoundMessage::ListAudio() {
	nCommandType = LISTAUDIO_COMMAND;

	return;
}