//---------------------------------------------------------------------------//
// File    : soundcore.cpp
// Author  : Rob Diaz-Marino
// Written : Feb 2004
//---------------------------------------------------------------------------//

// Windows includes
#include <windows.h>

// Standard ANSI-C includes
#include <string.h>
#include <stdio.h>
#define STL_USING_ALL
#include "stl.h"
#include "SoundCore.h"

using namespace std;

//===========================================================================//
// CLASS: CSFXThread
// Desc: Thread for monitoring all sound effects.
// Overview:
//   This class is used for monitoring the pool of sound effects in the
//   soundcore, so that during playback, when the sound terminates, the
//   object state is updated accordingly.
//
//   A single instance of this class is meant to be placed within the
//   CSoundCore class.
//===========================================================================//

//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CSFXThread::~CSFXThread() {
	m_cSCParent = NULL;
}

//---------------------------------------------------------------------------//
// Initializer
//---------------------------------------------------------------------------//
void CSFXThread::Init(CSoundCore *cSCNewParent) {
	m_cSCParent = cSCNewParent;
	m_bRunning = FALSE;
}

//---------------------------------------------------------------------------//
// Code that is run on this thread
//---------------------------------------------------------------------------//
void CSFXThread::run() {
	// Flag this thread as having started running
	m_bRunning = TRUE;

	DWORD dwEventNum;
	CSoundEffect *cSfx;
	MSG lpMsg;
	int i = 0;  // Loop variable

	ZeroMemory(&lpMsg, sizeof(MSG));

	// We need this stupid structure to set a timeout value on the timer we're
	// about to initialize.
	LARGE_INTEGER liTimerRate;
	liTimerRate.QuadPart = -1000000;

	// We have allocated a timer in the m_hSfxEnd handle array, with index
	// MAX_SOUND_VOICES.  Here is where we start the timer.  It is periodic,
	// so it goes off every FADE_TIMER_RATE milliseconds.
	SetWaitableTimer(m_cSCParent->m_hSfxEnd[MAX_SOUND_VOICES], &liTimerRate,
		FADE_TIMER_RATE, NULL, NULL, FALSE);

	// Loop as long as the thread termination flag has not been set
	while ( canRun() ) {

		// This command suspends the current thread until one of the event
		// handles is flagged.  The return value, dwEventNum, is the index of
		// the event in the m_hSfxEnd array.
		dwEventNum = MsgWaitForMultipleObjectsEx
			(MAX_SOUND_VOICES + 1, m_cSCParent->m_hSfxEnd, INFINITE,
			QS_ALLINPUT, MWMO_ALERTABLE | MWMO_INPUTAVAILABLE );

		// Check and see if the returned index matches one of the
		// Sound Effect's end notifications.
		if( (dwEventNum >= 0) && (dwEventNum < MAX_SOUND_VOICES) ) {
			// This code is called every time the end of an SFX buffer is
			// reached. We must retrieve a pointer to the Sound Effect in
			// question, and call it's Stop() method.
			cSfx = &m_cSCParent->m_sfx[(int) dwEventNum];
			if (cSfx->m_bLooping == FALSE || cSfx->m_bSelfDestruct == TRUE) {
				cSfx->Stop();
				if( cSfx->m_bSelfDestruct ) cSfx->Release();
			}

		}
		else if ( dwEventNum == MAX_SOUND_VOICES ) {
			// This code is called every time the timer goes off.  It's meant
			// to adjust the fade volumes of all streams so that fade-in or
			// fade-out effects occur.
			for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
				if ( (m_cSCParent->m_stream[i].IsPlaying() == TRUE) &&
					 (m_cSCParent->m_stream[i].IsPaused() == FALSE) ) {
					m_cSCParent->m_stream[i].FadeStep();
					m_cSCParent->m_stream[i].BendStep();
					m_cSCParent->m_stream[i].SlideStep();
				}
			}

		}
		else {
			// The MsgWaitForMultipleObjectsEx returns a value of
			// MAX_SOUND_VOICES + 1 to indicate that a message is waiting.
			// We must retrieve this message or it will constantly get booted out
			// of the MsgWaitForMultipleObjectsEx function until it's cleared.
			if (PeekMessage(&lpMsg, m_cSCParent->m_hWnd, 0, 0, TRUE)) {
				DispatchMessage(&lpMsg);
			}
		}

	}  // end while

	// The timer is deactivated here.  The handle must still be closed, however
	// this is done in the SoundCore destructor along with all the other handles.
	CancelWaitableTimer( m_cSCParent->m_hSfxEnd[MAX_SOUND_VOICES] );

	// Flag this thread as having terminated
	m_bRunning = FALSE;
}



//===========================================================================//
// CLASS: CStreamThread
// Desc:
//   This class is used for monitoring an individual CSoundStream object
//   and refreshing the streaming data when the notification is sent, or
//   stopping the stream if it is not meant to loop infinitely.
//===========================================================================//

//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CStreamThread::~CStreamThread() {
	m_cSCParent = NULL;
}

//---------------------------------------------------------------------------//
// Initializer
//---------------------------------------------------------------------------//
void CStreamThread::Init(CSoundStream *cSCNewParent) {
	m_cSCParent = cSCNewParent;
	m_bRunning = FALSE;
}

//---------------------------------------------------------------------------//
// Code that is run on this thread
//---------------------------------------------------------------------------//
void CStreamThread::run() {
	// Flag this thread as having started running
	m_bRunning = TRUE;

	HRESULT hr = NO_ERROR;
	DWORD dwEventNum;
	MSG lpMsg;

	ZeroMemory(&lpMsg, sizeof(MSG));

	// Loop as long as the thread termination flag has not been set
	while ( canRun() ) {

		// This command suspends the current thread until one of the event
		// handles is flagged.  The return value, dwEventNum, is the index of
		// the event in the m_hSfxEnd array.
		dwEventNum = MsgWaitForMultipleObjectsEx
			(STREAM_REFRESH_POINTS, m_cSCParent->m_hRefresh, FADE_TIMER_RATE,
			QS_ALLINPUT, MWMO_ALERTABLE | MWMO_INPUTAVAILABLE );

		if( dwEventNum == WAIT_TIMEOUT ) continue;

		// Check and see if the returned index matches one of the
		// Sound Stream's end refresh.
		if( (dwEventNum >= 0) && (dwEventNum < STREAM_REFRESH_POINTS) ) {

			// Load the next chunk of data.
			// If this isn't a looping stream and we've reached the end of
			// the data, but this doesn't mean we need to suspend the thread.
			// It can continue running with minimal overhead.
			hr = m_cSCParent->UpdateData( dwEventNum );
			if( (FAILED( hr )) || (hr == ERROR_NO_DATA) ) {
				m_cSCParent->Stop();
				if( m_cSCParent->m_bSelfDestruct ) m_cSCParent->Release();
			}

		}
		else {
			// The MsgWaitForMultipleObjectsEx returns a value of STREAM_REFRESH_POINTS + 1 to
			// indicate that a message is waiting.  We must retrieve this message or it will
			// constantly get booted out of the wait until it is cleared.
			if (PeekMessage(&lpMsg, m_cSCParent->m_cSCParent->m_hWnd, 0, 0, TRUE)) {
				DispatchMessage(&lpMsg);
			}
		}


	}  // end while

	// Flag this thread as having terminated
	m_bRunning = FALSE;
}



//===========================================================================//
// CLASS: CSoundCore
// Desc:
//   This class is the the main component of the sound engine that houses
//   all sound effect and stream pools.  In these pools, all sound objects
//   are recycled.  The GetSoundEffect(c,*C) and GetSoundStream(c,*C)
//   functions provide a way to quickly locate a sound object in the pool
//   that is not currently being used.  The pointer to the object is
//   returned in the *C parameter.
//
//   This class is also responsible for controlling the master volume, and
//   adjusting the volume of all sounds when this is changed.
//   Volume ranges from MAX_VOLUME (0) to MIN_VOLUME (-10000) -
//   this scale is used for SetMasterVolume(l) and is returned in
//   GetMasterVolume().  The SetMasterVolume(f) takes a float value from
//   0 to 1, where 0 is silent and 1 is full.  This is a slightly more
//   intuitive scale to deal with.
//
//   The Suspend() and Resume() functions can be used to pause and unpause
//   all sound objects in the two pools.  The IsSuspended() method can be
//   used to check if the Sound Core is currently suspended or not.  Any
//   sounds that are played while the core is suspended will automatically
//   be paused, but will begin playing as soon as the core is resumed.
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSoundCore::CSoundCore()
{
	// Initialize all variables and objects
	m_hWnd = NULL;
	m_lpDS = NULL;
	m_bSuspended = FALSE;

	// Initialize volume
	m_lVolume = 0;

	// Initialize sfx pool
	m_sfx = new CSoundEffect[ MAX_SOUND_VOICES ];

	// Initialize stream pool
	m_stream = new CSoundStream[ MAX_SOUND_STREAMS ];

	// Initialize the SFX Checker thread
	m_cSTSFXCheck = new CSFXThread();

}

//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CSoundCore::~CSoundCore() {
	Destroy();
}


//---------------------------------------------------------------------------//
// NAME: Init
// DESC:
//   Initialize the Sound Core.
// PARAMETERS:
//   hWndNew - Windows handle to the main window for this application.
//   lCoopLevel - Cooperative level, needed for initializing DirectSound.
//                Must be one of the following values:
//                DSSCL_NORMAL, DSSCL_PRIORITY (recommended), DSSCL_EXCLUSIVE,
//                or DSSCL_WRITEPRIMARY
// RETURNS:
//   NO_ERROR - when initialization successful.
//   otherwise - DirectSound error message when not successful.
//---------------------------------------------------------------------------//
HRESULT CSoundCore::Init( HWND hWndNew, long lCoopLevel ) {
	HRESULT hr = NO_ERROR;
	int i;

	// Set the HWND for the sound core
	m_hWnd = hWndNew;

	// Initialize DirectSound interface if necessary
	if ( FAILED( hr = DirectSoundCreate8(NULL, &m_lpDS, NULL) ) ) {
		// Error occurred
		SOUNDCORE_ERROR( "Failed to create DirectSound instance", hr, "CSoundCore::Init(h,l)" );
		return hr;
	}

	// Try to set the Cooperative level
	if ( FAILED( hr = m_lpDS->SetCooperativeLevel( m_hWnd, lCoopLevel ) ) ) {
		// Error occurred
		SOUNDCORE_ERROR( "Failed to set co-operative level", hr, "CSoundCore::Init(h,1)" );
		return hr;
	}

	// Initialize sfx array
	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		m_sfx[i].Init( this, i );
	}

	// Initialize array of SFX Stop notifications
	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		m_hSfxEnd[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	// Initialize last index to a timer handle for fade effects
	m_hSfxEnd[MAX_SOUND_VOICES] = CreateWaitableTimer(NULL, FALSE, NULL);

	// Initialize stream array
	for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		m_stream[i].Init( this, i );
	}

	// Start the sound effects checking thread
	m_cSTSFXCheck->Init( this );

	if (!m_cSTSFXCheck->create()) {
		SOUNDCORE_MESSAGE( "Error: Could not spawn checker thread in CSoundCore::Start()" );
		m_cSTSFXCheck = NULL;
		return ERROR_INVALID_THREAD_ID;
	}

	m_cSTSFXCheck->start();

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Destroy
// DESC:
//   Destroy the Sound Core.
//---------------------------------------------------------------------------//
void CSoundCore::Destroy() {
	int i = 0;  // Loop variable

	// Stop all sound streams
	for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		m_stream[i].Stop();
	}

	// Stop all sound effects
	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		m_sfx[i].Stop();
	}

	// Destroy Sound checker thread
	m_cSTSFXCheck->shutdown();

	// Wait for thread to terminate itself
	while( (volatile) m_cSTSFXCheck->IsRunning() ) {}

	if (m_cSTSFXCheck) delete m_cSTSFXCheck;

	// Destroy sound stream pool
	delete[] m_stream;

	// Destroy array of SFX Stop notifications
	for( i = 0; i < MAX_SOUND_VOICES + 1; i++ ) {
		CloseHandle( m_hSfxEnd[i] );
	}

	// Destroy sound effect pool
	delete[] m_sfx;

	return;
}



//---------------------------------------------------------------------------//
// NAME: GetSoundCore
// DESC: Get the static singleton instance of the SoundCore.
//---------------------------------------------------------------------------//
CSoundCore &CSoundCore::GetSoundCore()
{
  static CSoundCore m_SoundCore;  // instantiate this singleton class on first use
  return  m_SoundCore;
}


//---------------------------------------------------------------------------//
// NAME: GetSoundCorePtr
// DESC: Get a pointer to the static singleton instance of the SoundCore.
//---------------------------------------------------------------------------//
CSoundCore *CSoundCore::GetSoundCorePtr()
{
  return &GetSoundCore();
}


//---------------------------------------------------------------------------//
// NAME: GetSoundEffect
// DESC:
//   Dispatch the next free sound effect.
// PARAMETERS:
//   cSoundName - name of the file to be played.  Must be in the SOUND_PATH
//                directory.  Do not include .WAV extension, this is
//                automatically appended to the name you specify.
//   ref - pointer to the pointer that will accept the object reference.
//         You follow? :P  For example, you declare a sound effect as such:
//           CSoundEffect *sfx;
//         Then you call this function to get the object:
//           GetSoundEffect("file", &sfx);
//         And now you can use the returned sound object.
//           sfx->Play();
//         OR if you just want to toss in a sound effect without any
//         control of it whatsoever, don't include the ref.  This type of
//         sound plays once at full volume, and is automatically destroyed:
//           GetSoundEffect("file");
//         Use one of the following to check if there were no free sounds:
//           if( ref == NULL ) then you're plain out of luck.
//           if(FAILED( GetSoundEffect("file", &sfx) )) then bite me.
// RETURNS:
//   NO_ERROR - the operation was successful
//   ERROR_OUT_OF_STRUCTURES - no free sound effects
//---------------------------------------------------------------------------//
HRESULT CSoundCore::GetSoundEffect( const char* cSoundName, CSoundEffect **ref ) {
	CSoundEffect *retSound = NULL;

	// Locate the first unlocked sound effect
	for( int i = 0; i < MAX_SOUND_VOICES; i++ ) {
		if ( m_sfx[i].IsLocked() == FALSE ) {
			// Lock the sound before anyone else gets a chance
			m_sfx[i].m_bLocked = TRUE;
			retSound = &m_sfx[i];
			break;
		}
	}

	// No unlocked sounds
	if( retSound == NULL ) {
		SOUNDCORE_MESSAGE("Error: No free sound effects!");
		*ref = NULL;
		return ERROR_OUT_OF_STRUCTURES;
	}

	// Prepare the sound buffer
	retSound->Load( cSoundName );

	// If the reference is null, then we don't have to return a reference
	if( ref != NULL ) {
		*ref = retSound;
	}
	else {
		retSound->m_bSelfDestruct = TRUE;
		retSound->Play( FALSE, FALSE );
	}

	return NO_ERROR;
}


//---------------------------------------------------------------------------//
// NAME: GetSoundEffect
// DESC:
//   Dispatch the next free stream.
// PARAMETERS:
//   cMusicName - name of the file to be played.  Must be in the MUSIC_PATH
//                directory.  Do not include .WAV extension, this is
//                automatically appended to the name you specify.
//   ref - pointer to the pointer that will accept the object reference.
//         You follow? :P  For example, you declare a stream as such:
//           CSoundStream *stream;
//         Then you call this function to get the object:
//           GetSoundStream("music", &stream);
//         And now you can use the returned sound object.
//           stream->Play();
//         OR if you just want to toss in music without any
//         control of it whatsoever, don't include the ref.  This type of
//         sound plays once at full volume, and is automatically destroyed:
//           GetSoundStream("music");
//         Use one of the following to check if there were no free streams:
//           if( ref == NULL ) then you're plain out of luck.
//           if(FAILED( GetSoundStream("music", &stream) )) then bite me.
// RETURNS:
//   NO_ERROR - the operation was successful
//   ERROR_OUT_OF_STRUCTURES - no free sound effects
//---------------------------------------------------------------------------//
HRESULT CSoundCore::GetSoundStream( const char* cMusicName, CSoundStream **ref ) {
	HRESULT hr = NO_ERROR;
	CSoundStream *retSound = NULL;

	// Locate the first unlocked sound stream
	for( int i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		if ( m_stream[i].IsLocked() == FALSE ) {
			// Lock the sound before anyone else gets a chance
			m_stream[i].m_bLocked = TRUE;
			retSound = &m_stream[i];
			break;
		}
	}

	// No unlocked sounds
	if( retSound == NULL ) {
		SOUNDCORE_MESSAGE("Error: No free sound streams!");
		return ERROR_OUT_OF_STRUCTURES;
	}

	// Prepare the sound buffer
	hr = retSound->Load( cMusicName );

	// If the reference is null, then we don't have to return a reference
	if( ref != NULL ) {
		*ref = retSound;
	}
	else {
		retSound->m_bSelfDestruct = TRUE;
		retSound->SetVolume(0L);
		
		if(FAILED( hr = retSound->Play( FALSE, FALSE ) )) {
			// Error occurred
			retSound->m_bLocked = FALSE;
			return hr;
		}
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: SetMasterVolume
// DESC:
//   Method to set the current master volume.
// PARAMETERS:
//   lTargetVolume - new volume value. Values can range from
//   MAX_VOLUME (0) to MIN_VOLUME (-10000).
// RETURNS:
//   NO_ERROR - operation was successful.
//   ERROR_INVALID_DATA - value was not in the valid range.
//---------------------------------------------------------------------------//
HRESULT CSoundCore::SetMasterVolume( long lTargetVolume ) {
	int i = 0;	// Loop variable

	// Ensure the volume is between -10000 and 0
	if ( (lTargetVolume > MAX_VOLUME) || (lTargetVolume < MIN_VOLUME ) )
		return ERROR_INVALID_DATA;

	// Volume change succeeded
	m_lVolume = lTargetVolume;

	// Update the volumes for all sound effects accordingly
	for (i = 0; i < MAX_SOUND_VOICES; i++) {
		m_sfx[i].RefreshVolume();
	}

	// Update the volumes for all sound streams accordingly
	for (i = 0; i < MAX_SOUND_STREAMS; i++) {
		m_stream[i].RefreshVolume();
	}

	return NO_ERROR;
}


//---------------------------------------------------------------------------//
// NAME: Suspend
// DESC:
//   Place the SoundCore in a dormant state in such a way that it can be
//   restored to it's current state at a later time.  Essentially this just
//   pauses all the sound effects and streams.
//---------------------------------------------------------------------------//
void CSoundCore::Suspend() {
	int i = 0;  // Loop variable

	m_bSuspended = TRUE;

	// Pause all the streams
	for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		m_stream[i].Pause();
	}

	// Pause all the sound effects
	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		m_sfx[i].Pause();
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: Suspend
// DESC:
//   Restore the SoundCore from a dormant state.  Essentially this just
//   unpauses all the sound effects and streams.
//---------------------------------------------------------------------------//
void CSoundCore::Resume() {
	int i = 0;  // Loop variable

	// Unpause all the streams
	for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		m_stream[i].Unpause();
	}

	// Unpause all the sound effects
	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		m_sfx[i].Unpause();
	}

	m_bSuspended = FALSE;

	return;
}


//---------------------------------------------------------------------------//
// NAME: LogError
// DESC:
//   Method to report error information for debugging purposes.
// PARAMETERS:
//   sErrMsg - string to describe the nature of the error.
//   hr - HRESULT of the error.
//   sErrLoc - string to describe the location of the error.
//---------------------------------------------------------------------------//
void CSoundCore::LogError( char *sErrMsg, HRESULT hr, char *sErrLoc ) {
	char sMessage[255] = "Error ";
	char sHRBuffer[ sizeof(long) * 8 + 1 ];

	ltoa(hr, sHRBuffer, 10);

	strcat(sMessage, sHRBuffer);
	strcat(sMessage, ": ");
	strcat(sMessage, sErrMsg);
	strcat(sMessage, "\nin ");
	strcat(sMessage, sErrLoc);

#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, sMessage);
#endif

	return;
}


//---------------------------------------------------------------------------//
// NAME: LogMessage
// DESC:
//   Method to output a message for debug purposes.
// PARAMETERS:
//   sMsg - string to output.
//---------------------------------------------------------------------------//
void CSoundCore::LogMessage( char *sMsg ) {

#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, sMsg);
#endif

	return;
}



//---------------------------------------------------------------------------//
// NAME: GetFreeSoundEffects
// DESC:
//   Get a count of the number of sound effects that are unused.
// RETURNS:
//   int - number of free sound effects.
//---------------------------------------------------------------------------//
int CSoundCore::GetFreeSoundEffects() {
	int i = 0, freecount = 0;

	for( i = 0; i < MAX_SOUND_VOICES; i++ ) {
		if ( m_sfx[i].IsLocked() == TRUE ) freecount++;
	}

	return freecount;
}


//---------------------------------------------------------------------------//
// NAME: GetFreeSoundStreams
// DESC:
//   Get a count of the number of sound streams that are unused.
// RETURNS:
//   int - number of free sound streams.
//---------------------------------------------------------------------------//
int CSoundCore::GetFreeSoundStreams() {
	int i = 0, freecount = 0;

	for( i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		if ( m_stream[i].IsLocked() == TRUE ) freecount++;
	}

	return freecount;
}



//---------------------------------------------------------------------------//
// NAME: ResetSFX
// DESC:
//   Release all sound effects (DANGER: This may leave pointers still
//   referring to the uninitialized object!!)
//---------------------------------------------------------------------------//
void CSoundCore::ResetSFX() {
	// Loop through all sound effects and release all that are locked
	for( int i = 0; i < MAX_SOUND_VOICES; i++ ) {
		if ( m_sfx[i].IsLocked() == TRUE ) m_sfx[i].Release();
	}
	return;
}


//---------------------------------------------------------------------------//
// NAME: ResetStreams
// DESC:
//   Release all sound streams (DANGER: This may leave pointers still
//   referring to the uninitialized object!!)
//---------------------------------------------------------------------------//
void CSoundCore::ResetStreams() {
	// Loop through all sound streams and release all that are locked
	for( int i = 0; i < MAX_SOUND_STREAMS; i++ ) {
		if ( m_stream[i].IsLocked() == TRUE ) m_stream[i].Release();
	}
	return;
}


//---------------------------------------------------------------------------//
// NAME: ResetAll
// DESC:
//   Release everything (DANGER: This may leave pointers still
//   referring to the uninitialized object!!)
//---------------------------------------------------------------------------//
void CSoundCore::ResetAll() {
	ResetSFX();
	ResetStreams();

	return;
}

//----------------------------------- EOF ------------------------------------//