//---------------------------------------------------------------------------//
// File    : soundcore.h
// Author  : Rob Diaz-Marino
// Written : Feb 2004
//---------------------------------------------------------------------------//

#ifndef _SOUNDMESSAGE_H_
#define _SOUNDMESSAGE_H_

#include "bos.h"
#include "windows.h"

#include "task.h"

// #defines
#define MAX_FILENAME_LEN 260
#define MAX_ID_LEN 32


// Commands
#define NO_COMMAND 0

#define PLAYSOUNDEFFECTONCE_COMMAND 1
#define LOADSOUNDEFFECT_COMMAND 2
#define PLAYSOUNDEFFECT_COMMAND 3
#define PAUSESOUNDEFFECT_COMMAND 4
#define UNPAUSESOUNDEFFECT_COMMAND 5
#define STOPSOUNDEFFECT_COMMAND 6
#define RELEASESOUNDEFFECT_COMMAND 7

#define PLAYSTREAMONCE_COMMAND 16
#define LOADSTREAM_COMMAND 17
#define PLAYSTREAM_COMMAND 18
#define PAUSESTREAM_COMMAND 19
#define UNPAUSESTREAM_COMMAND 20
#define STOPSTREAM_COMMAND 21
#define RELEASESTREAM_COMMAND 22
#define FADEINSTREAM_COMMAND 23
#define FADEOUTSTREAM_COMMAND 24

#define LISTAUDIO_COMMAND 32

#define PLAYLIST_LOAD_COMMAND 64
#define PLAYLIST_PLAY_COMMAND 65
#define PLAYLIST_STOP_COMMAND 66
#define PLAYLIST_PAUSE_COMMAND 67
#define PLAYLIST_UNPAUSE_COMMAND 68


// Forward Class Definitions
class CSoundID;
class CSoundMessage;

// Operators
bool operator<(CSoundID a, CSoundID b);
bool operator>(CSoundID a, CSoundID b);



class CSoundID
{
private:
	char m_str[MAX_ID_LEN];

public:
	CSoundID() { strcpy( m_str, "" ); }
	CSoundID( char *ID ) { strcpy( m_str, ID ); }
	char *getID() { return m_str; }
	void setID( char *ID ) { strcpy( m_str, ID ); }
};



class CSoundMessage : public ITaskMessage
{
public:
	// Public properties
	char nCommandType;		// Type of command this is
	char cSoundID[MAX_ID_LEN];   // ID of the sound
	char cSoundName[MAX_FILENAME_LEN];   // Name of the sound file
	float fVolume;			// Volume to play sound at
	bool bLooped;			// Is the sound played looped or one-shot
	bool bPause;			// Pause the sound
	bool bUnpause;			// Unpause the sound
	bool bStop;				// Stop the sound
	bool bFadeIn;			// Fade the sound in
	float fFadeStartPerc;	// Starting volume percent when fading in
	bool bFadeOut;			// Fade the sound out
	int nFadeStep;			// Step size while fading in/out
	char cCrossFade[MAX_FILENAME_LEN];	// Name of sound to crossfade with.  "" means no crossfade.

	// Constructor
	CSoundMessage();
	~CSoundMessage() {};

	// Predefined Actions
    void PlaySoundEffectOnce( std::string sNewName );
    void PlaySoundEffect( std::string sID, bool loop );
    void LoadSoundEffect( std::string sNewName, std::string sNewID );
    void StopSoundEffect( std::string sID );
    void PauseSoundEffect( std::string sID );
    void UnpauseSoundEffect( std::string sID );
    void ReleaseSoundEffect( std::string sID );

    void PlayStreamOnce( std::string sNewName );
    void PlayStream( std::string sID, bool loop );
    void LoadStream( std::string sNewName, std::string sNewID );
    void StopStream( std::string sID );
    void PauseStream( std::string sID );
    void UnpauseStream( std::string sID );
    void ReleaseStream( std::string sID );

    void PlayList( float fVolume, bool bAutoRepeat, bool bAutoAdvance );
    void LoadList( std::string sListFile );
    void StopList();
    void PauseList();
    void UnpauseList();

	void ListAudio();

protected:
private:
};

#endif