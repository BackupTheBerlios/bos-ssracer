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
#define NO_COMMAND 0
#define PLAYSOUNDEFFECTONCE_COMMAND 1
#define PLAYMUSIC_COMMAND 2
#define STOPMUSIC_COMMAND 3
#define PLAYAMBIENT_COMMAND 4
#define STOPAMBIENT_COMMAND 5


// Forward Class Definitions
class CSoundMessage;

//---------------------------------------------------------------------------//
// Name: sSoundCommand
// Desc: Convey a command to the SoundCore through a message.
//---------------------------------------------------------------------------//
typedef struct sSoundCommand {
	char nCommandType;		// Type of command this is
	char cSoundName[MAX_FILENAME_LEN];   // Name of the sound file to load
	float fVolume;			// Volume to play sound at
	bool bLooped;			// Is the sound played looped or one-shot
	bool bIsSound;			// Type of target: TRUE=sfx, FALSE=stream
	bool bPause;			// Pause the sound
	bool bUnpause;			// Unpause the sound
	bool bStop;				// Stop the sound
	bool bFadeIn;			// Fade the sound in
	float fFadeStartPerc;	// Starting volume percent when fading in
	bool bFadeOut;			// Fade the sound out
	int nFadeStep;			// Step size while fading in/out
	char cCrossFade[MAX_FILENAME_LEN];	// Name of sound to crossfade with.  "" means no crossfade.
} sSoundCommand;


class CSoundMessage : public ITaskMessage
{
public:
	// Public properties
	sSoundCommand m_sCommand;  // Store sound command

	// Constructor
	CSoundMessage();
	~CSoundMessage() {};
	void SetID( char* cNewID );
	void SetName( char* cNewName );
	void SetFadeTo( char* cNewName );

	// Predefined Actions
    void PlaySoundEffectOnce( char* cNewName );
	void PlayMusic( char* cNewName, bool bLooped, float fVolume );
	void StopMusic();
	void PlayAmbient( char* cNewName, bool bLooped, float fVolume );
	void StopAmbient();

protected:
private:
};

#endif