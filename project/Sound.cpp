//---------------------------------------------------------------------------//
// File    : sound.cpp
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


//===========================================================================//
// CLASS: CSound
// Desc: 
//   Base class from which all sound objects inherit.  Contains some
//   fundamental components common to all of them, such as a DirectSound
//   buffer, and state information flags.
//
//   THIS CLASS SHOULD NOT BE INSTANTIATED - virtual functions with an
//   HRESULT return type will all give back an ERROR_NOT_SUPPORTED error
//   if called.
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSound::CSound() {
	m_cSCParent = NULL;
	m_lpDSBuffer = NULL;

	m_bPlaying = FALSE;
	m_bLocked = FALSE;
	m_bSelfDestruct = FALSE;

	m_lVolume = 0;
	m_ulFrequency = 0;
	m_lPan = 0;
}

//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CSound::~CSound() {
	Destroy();
}


//---------------------------------------------------------------------------//
// NAME: Init
// DESC: Initialize the sound object.
// PARAMETERS:
//   cSCNewParent - pointer to the CSoundCore object that this sound object
//                  belongs to.
//   nNewId - integer ID for this particular sound, typically the index of
//            this object in the sound effect or stream pool.
// RETURNS:
//   NO_ERROR - operation completed successfully.  Let's face it - there's
//              not a lot that can go wrong here...
//---------------------------------------------------------------------------//
HRESULT CSound::Init( CSoundCore *cSCNewParent, int nNewId ) {
	m_cSCParent = cSCNewParent;
	m_nId = nNewId;
	return NO_ERROR;
}


//---------------------------------------------------------------------------//
// NAME: Destroy
// DESC: Destroyer of sound objects.  Sound objects quiver in fear when
//       they hear it's name.  Beware, little sound objects, run away!
//---------------------------------------------------------------------------//
void CSound::Destroy() {
	m_cSCParent = NULL;

	// Destroy the buffer
	if(m_lpDSBuffer != NULL) {
		m_lpDSBuffer->Release();
		m_lpDSBuffer = NULL;
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: SetVolume (overloaded)
// DESC: Method to set the current volume.
// PARAMETERS:
//   fVolPercent - floating point number between 0 (mute) and 1 (full)
//                 to indicate volume percentage.
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSound::SetVolume( float fVolPercent ) {
	long lTargetVolume = 0;
	long lNewVolume = 0;
	HRESULT hr = NO_ERROR;
	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	// Ensure the percentage is between 0 and 1
	if ( (fVolPercent > 1) || (fVolPercent < 0) )
		return FALSE;

	// Clamp the result of adding the master volume and target volume together
	lTargetVolume = (long) ( ((float) 1 - fVolPercent) * MIN_VOLUME );
	lNewVolume = m_cSCParent->m_lVolume + lTargetVolume;
	if (lNewVolume > MAX_VOLUME) lNewVolume = MAX_VOLUME;
	if (lNewVolume < MIN_VOLUME) lNewVolume = MIN_VOLUME;

	// Ensure the buffer exists
	if( m_lpDSBuffer == NULL ) return hr;

	// Change the volume in the buffer using the master and local volumes
	if ( FAILED( hr = 
		m_lpDSBuffer->SetVolume( m_cSCParent->m_lVolume + lNewVolume ) ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to set volume.", hr, "CSound::SetVolume(f)" ); 
		return hr;
	}

	// Volume change succeeded
	m_lVolume = lTargetVolume;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: SetVolume (overloaded)
// DESC: Method to set the current volume.
// PARAMETERS:
//   fVolPercent - long number between -10000 (mute) and 0 (full).
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSound::SetVolume( long lTargetVolume ) {
	long lNewVolume;
	HRESULT hr = NO_ERROR;
	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	// Ensure the volume is between -10000 and 0
	if ( (lTargetVolume > MAX_VOLUME) || (lTargetVolume < MIN_VOLUME ) )
		return FALSE;

	// Clamp the result of adding the master volume and target volume together
	lNewVolume = m_cSCParent->m_lVolume + lTargetVolume;
	if (lNewVolume > MAX_VOLUME) lNewVolume = MAX_VOLUME;
	if (lNewVolume < MIN_VOLUME) lNewVolume = MIN_VOLUME;

	// Ensure the buffer exists
	if( m_lpDSBuffer == NULL ) return hr;

	// Change the volume in the buffer using the master and local volumes
	if ( FAILED( hr = m_lpDSBuffer->SetVolume( lNewVolume ) ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to set volume.", hr, "CSound::SetVolume(l)" ); 
		return hr;
	}

	// Volume change succeeded
	m_lVolume = lTargetVolume;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: SetFrequency
// DESC: Method to set the current frequency.  Note that frequency affects
//       the rate at which a sound is played, thus increasing it makes the
//       sound play faster and sound higher-pitched, while decreasing it
//       makes the sound play slower and at a lower pitch.
// PARAMETERS:
//   ulNewFrequency - long number, usually one of 11050, 22100, 44200.
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSound::SetFrequency( unsigned long ulNewFrequency ) {
	HRESULT hr = NO_ERROR;
	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	// Ensure the buffer exists
	if( m_lpDSBuffer == NULL ) return FALSE;

	// Change the frequency in the buffer using the given value
	if ( FAILED( hr = m_lpDSBuffer->SetFrequency( ulNewFrequency ) ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to set frequency.", hr, "CSound::SetFrequency(ul)" );
		return FALSE;
	}

	// Frequency change succeeded
	m_ulFrequency = ulNewFrequency;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: SetPan
// DESC: Method to set the current pan.  Pan defines the proportional volume
//       at which the sound is played between the left and right speaker.
// PARAMETERS:
//   lNewPan - long number between MAX_PAN_LEFT (-10000) and MAX_PAN_RIGHT
//             (10000), with the value of PAN_CENTER (0) being in the middle.
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSound::SetPan( long lNewPan ) {
	HRESULT hr = NO_ERROR;
	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	// Ensure the volume is between -10000 and 0
	if ( (lNewPan < MAX_PAN_LEFT) || (lNewPan > MAX_PAN_RIGHT ) )
		return FALSE;

	// Ensure the buffer exists
	if( m_lpDSBuffer == NULL ) return hr;

	// Change the pan in the buffer using the given value
	if ( FAILED( hr = m_lpDSBuffer->SetPan( lNewPan ) ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to set pan.", hr, "CSound::SetPan(l)" );
		return FALSE;
	}

	// Pan change succeeded
	m_lPan = lNewPan;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: RefreshVolume
// DESC: Readjust the volume based on master settings.
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSound::RefreshVolume() {
	HRESULT hr = NO_ERROR;
	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	// Change the volume in the buffer using the master and local volumes
	if ( FAILED( hr = 
		m_lpDSBuffer->SetVolume( m_cSCParent->m_lVolume + m_lVolume ) ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to refresh volume.", hr, "CSound::RefreshVolume()" ); 
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Load
// DESC: Basically just a stub that must be overloaded in the
//       inheriting classes.
// PARAMETERS:
//   cSoundName - doesn't matter for now, only needed in overloaded methods
// RETURNS:
//   ERROR_NOT_SUPPORTED
//---------------------------------------------------------------------------//
HRESULT CSound::Load( char *cSoundName ) {
	// This is just to satisfy the compiler as not to get any unreferenced
	// local variable warnings...
	strcmp(cSoundName, "");

	// Classes that inherit from CSound MUST implement this method.  We
	// will always return an error message to notify them that they shouldn't
	// be using the virtual one.
	return ERROR_NOT_SUPPORTED;
}


//---------------------------------------------------------------------------//
// NAME: GetWAVHeader
// DESC: Get a WAV's header information.
// PARAMETERS:
//   cFilename - path, name, and extension of file to get info from.
// RETURNS:
//   NO_ERROR - header info retrieved without a hitch.
//   ERROR_FILE_NOT_FOUND - monkeys always look :P
//   ERROR_BAD_FORMAT - the format of the WAV header did not match what
//                      we were expecting.  Thus the file may be bad.
//---------------------------------------------------------------------------//
HRESULT CSound::GetWAVHeader( char *cFilename ) {
	HRESULT hr = NO_ERROR;
	FILE *fp;

	// Open the source file
	if ( (fp = fopen(cFilename, "rb")) == NULL) {
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, "Could not open file \"%s\" in CSound::GetWAVHeader(c).", cFilename);
#endif
		return ERROR_FILE_NOT_FOUND;
	}

	// Read in the header from the beginning of the file
	fseek(fp, 0, SEEK_SET);
	fread(&m_swHeader, 1, sizeof(sWaveHeader), fp);

	// Check the sig fields, return if an error
	if( memcmp(m_swHeader.cRiffSig, "RIFF", 4) ||
		memcmp(m_swHeader.cWaveSig, "WAVE", 4) ||
		memcmp(m_swHeader.cFormatSig, "fmt ", 4) ||
		memcmp(m_swHeader.cDataSig, "data", 4)) {

		// Error in expected header, return null to signify
		SOUND_MESSAGE("Error interpreting WAV file header in CSound::GetWavHeader(c).");
		fclose(fp);	
		return ERROR_BAD_FORMAT;
	}

	// Close the source file
	fclose(fp);	

	return hr;
}



//===========================================================================//
// CLASS: CSoundEffect
// Desc: 
//   This class stores a short WAV sound.  Longer files should use the
//   stream object instead, as this object loads the entire file data into
//   system memory!!
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSoundEffect::CSoundEffect() {}


//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CSoundEffect::~CSoundEffect() {
	Destroy();
}


//---------------------------------------------------------------------------//
// NAME: Init
// DESC: Initialize the sound effect object.  Essentially all this does is
//       call the base class constructor.
// PARAMETERS:
//   cSCNewParent - pointer to the CSoundCore object that this sound object
//                  belongs to.
//   nNewId - integer ID for this particular sound, typically the index of
//            this object in the sound effect or stream pool.
// RETURNS:
//   NO_ERROR - operation completed successfully.  Let's face it - there's
//              not a lot that can go wrong here...
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Init(CSoundCore *cSCNewParent, int nNewId) {
	HRESULT hr = NO_ERROR;

	if (FAILED( hr = CSound::Init( cSCNewParent, nNewId ) )) {
		SOUND_ERROR( "Failed to initialize base class", hr, "CSoundEffect::Init(C,n)" );
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Destroy
// DESC: Destroyer of sound objects.  Essentially this just calls the base
//       class destructor, as the Sound Effects object isn't too much
//       different.
//---------------------------------------------------------------------------//
void CSoundEffect::Destroy() {
	CSound::Destroy();
}


//---------------------------------------------------------------------------//
// NAME: Load
// DESC: Load the WAV data from a given sound effect into the buffer.
// PARAMETERS:
//   cSoundName - name of the sound file to be loaded.  Must be in the
//                SOUND_PATH directory.  DO NOT include the .WAV extension
//                as this is automatically appended.
// RETURNS:
//   NO_ERROR - sound loaded successfully.
//   ERROR_FILE_NOT_FOUND - duh!
//   Otherwise - see errors returned by CreateBufferFromWav() and
//               LoadSoundData(c,l,l).
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Load( char *cSoundName ) {
	HRESULT hr = NO_ERROR;

	// Create the filename from the sound name
	char cFilename[255] = SOUND_PATH;
	strcat( cFilename, cSoundName );
	strcat( cFilename, ".wav" );

	// Get the header information
	if ( FAILED( hr = GetWAVHeader( cFilename ) ) ) {
		SOUND_ERROR( "Could not get WAV Header", hr, "CSoundEffect::Load(c)" );
		return hr;
	}

	// Create the sound buffer
	if ( FAILED( hr = CreateBufferFromWAV() ) ) {
		SOUND_ERROR( "Buffer creation failed", hr, "CSoundEffect::Load(c)" );
		return hr;
	}

	// Read in the data
	if ( FAILED( hr = LoadSoundData(cFilename, 0, m_swHeader.lDataSize) ) ) {
		SOUND_ERROR( "Could not read sound data", hr, "CSoundEffect::Load(c)" );
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: CreateBufferFromWAV
// DESC: Create the DirectSound buffer using the WAV information stored in
//       the m_swHeader structure.  Note that this requires that the
//       GetWavHeader(c) function be called before this function.  Luckily
//       this is taken care of for you by the Load(c) function.
// RETURNS:
//   NO_ERROR - buffer created successfully.
//   ERROR_FILE_NOT_FOUND - duh!
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::CreateBufferFromWAV() {
	HRESULT hr = NO_ERROR;
	WAVEFORMATEX wfexFormat;
	DSBUFFERDESC dsbdBufferDesc;

	LPDIRECTSOUNDNOTIFY lpDSNotify;
	DSBPOSITIONNOTIFY dsbpNotify;

	// Set up playback format using header data
	ZeroMemory(&wfexFormat, sizeof(wfexFormat));
    wfexFormat.wFormatTag = WAVE_FORMAT_PCM; 
    wfexFormat.nChannels = m_swHeader.sChannels;
    wfexFormat.nSamplesPerSec = m_swHeader.lSampleRate; 
    wfexFormat.wBitsPerSample = m_swHeader.sBitsPerSample; 
    wfexFormat.nBlockAlign = (unsigned short) ((wfexFormat.wBitsPerSample / 8) *
		wfexFormat.nChannels); 
    wfexFormat.nAvgBytesPerSec = wfexFormat.nSamplesPerSec *
		wfexFormat.nBlockAlign; 

	// Set up buffer description using header data
	ZeroMemory(&dsbdBufferDesc, sizeof(dsbdBufferDesc));
    dsbdBufferDesc.dwSize = sizeof(DSBUFFERDESC); 
    dsbdBufferDesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPOSITIONNOTIFY;
    dsbdBufferDesc.dwBufferBytes = m_swHeader.lDataSize; 
    dsbdBufferDesc.lpwfxFormat = &wfexFormat; 

	// Create the buffer
	if ( FAILED( hr =
		m_cSCParent->m_lpDS->CreateSoundBuffer(
		&dsbdBufferDesc, &m_lpDSBuffer, NULL) ) ) {

		// Error occurred
		SOUND_ERROR( "Failed to create sound buffer", hr, "CSoundEffect::CreateBufferFromWAV()" );
		return hr;
	}

	// Setup the End of Buffer notification
	if (FAILED( hr =
		m_lpDSBuffer->QueryInterface(IID_IDirectSoundNotify8, (LPVOID*)&lpDSNotify) ) ) {
		SOUND_ERROR( "Failed to query Notify interface", hr, "CSoundEffect::CreateBufferFromWAV()" );
		return hr;
	}

	dsbpNotify.dwOffset = m_swHeader.lDataSize - 1;
	dsbpNotify.hEventNotify = m_cSCParent->m_hSfxEnd[ m_nId ];

	if (FAILED( hr = lpDSNotify->SetNotificationPositions(1, &dsbpNotify) )) {
	    lpDSNotify->Release();
		SOUND_ERROR( "Failed to set notification position", hr, "CSoundEffect::CreateBufferFromWAV()" );
		return hr;
	}

    lpDSNotify->Release();

	// Update sound properties
	m_lpDSBuffer->GetVolume(&m_lVolume);
	m_lpDSBuffer->GetFrequency(&m_ulFrequency);
	m_lpDSBuffer->GetPan(&m_lPan);

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: LoadSoundData
// DESC: Load the actual sound data from the WAV file into the buffer which
//       is created using the CreateBufferFromWAV() method.  This method is
//       used in the Load(c) method.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_FILE_NOT_FOUND - duh!
//   ERROR_INVALID_DATA - the lSize parameter is <= 0.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::LoadSoundData(char *cFilename, long lLockPos, long lSize) {
	HRESULT hr = NO_ERROR;
	BYTE *bPtr1, *bPtr2;
	DWORD dwSize1, dwSize2;
	FILE *fp;

	// Open the source file
	if ( (fp = fopen(cFilename, "rb")) == NULL) {

#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, 
			"Could not open file \"%s\" in CSoundEffect::LoadSoundData(c,l,l).",
			cFilename);
#endif

		return ERROR_FILE_NOT_FOUND;
	}

	// Seek to the beginning of WAV data
	fseek(fp, sizeof(sWaveHeader), SEEK_SET);

	if (lSize <= 0) {
		SOUND_MESSAGE( "Sound data size cannot be zero or negative." );
		return ERROR_INVALID_DATA;
	}

	// Lock the sound buffer at the position specified
	if ( FAILED( hr = m_lpDSBuffer->Lock(lLockPos, lSize, (void**)&bPtr1,
		&dwSize1, (void**)&bPtr2, &dwSize2, 0) ) ) {
		// Error occurred - unable to lock buffer
		SOUND_ERROR( "Unable to lock buffer", hr, "CSoundEffect::LoadSoundData(c,l,l)" );
		return hr;
	}

	// Read in the data
	fread(bPtr1, 1, dwSize1, fp);
	if (bPtr2 != NULL)
		fread(bPtr2, 1, dwSize2, fp);

	// Unlock the buffer
	m_lpDSBuffer->Unlock(bPtr1, dwSize1, bPtr2, dwSize2);

	// Close the file
	fclose(fp);

	// Return TRUE to indicate success
	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Reset
// DESC: Reset the play position to the beginning of the buffer.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Reset() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized
	if( m_lpDSBuffer == NULL) return ERROR_NOT_READY;

	// Attempt to set the buffer play position to the beginning of the buffer
	if(FAILED( hr = m_lpDSBuffer->SetCurrentPosition(0) )) {
		// Error occurred
		SOUND_ERROR( "Failed to set play position", hr, "CSoundEffect::Reset()" );
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Play
// DESC: Begin buffer playback.  Note that this function calls Reset() before
//       beginning playback, so the buffer will always start playback from
//       the beginning.
// PARAMETERS:
//   bLoop - Should the sound be played looping?
//           TRUE = loop playback infinitely until manually stopped.
//           FALSE = stop buffer automatically when the end is reached.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Play( BOOL bLoop, BOOL bPause ) {
	HRESULT hr = NO_ERROR;

	// Attempt to reset the play position to the beginning of the buffer
	if (( hr = Reset() ) != NO_ERROR ) {
		SOUND_ERROR( "Reset() failed", hr, "CSoundEffect::Play(b)" );
		return hr;
	}

	// If the core is suspended, simply pause it so that it will be
	// played when the core is resumed
	if ( m_cSCParent->IsSuspended() || bPause == TRUE ) {
		m_bPlaying = TRUE;
		m_bPaused = TRUE;
		return hr;
	}

	// We must specify if a buffer will be looped or not when we call it's
	// play function.
	if( bLoop == TRUE ) {
		m_bLooping = TRUE;

		// Play buffer looping
		if ( FAILED( hr = m_lpDSBuffer->Play(0, 0, DSBPLAY_LOOPING) ) ) {
			// Error occurred
			SOUND_ERROR( "Failed to play looping sound buffer", hr, "CSoundEffect::Play(b)" );
			return hr;
		}
	}
	else {
		m_bLooping = FALSE;

		// Play buffer looping
		if ( FAILED( hr = m_lpDSBuffer->Play(0, 0, 0) ) ) {
			// Error occurred
			SOUND_ERROR( "Failed to play sound buffer", hr, "CSoundEffect::Play(b)" );
			return hr;
		}
	}

	m_bPlaying = TRUE;
	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Stop
// DESC: Stop buffer playback.  Note that this function calls Reset() after
//       stopping playback, so if the buffer is played again, it will
//       start from the beginning.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Stop() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized
	if( m_lpDSBuffer == NULL) return ERROR_NOT_READY;

	// Attempt to stop playback
	if ( (m_lpDSBuffer == NULL) || FAILED( hr = m_lpDSBuffer->Stop() ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to stop buffer playback", hr, "CSoundEffect::Stop()" );
		return hr;
	}

	// Attempt to reset the play position to the beginning of the buffer
	if (FAILED( hr = Reset() )) {
		SOUND_ERROR( "Reset() failed", hr, "CSoundEffect::Play(b)" );
		return hr;
	}

	m_bPlaying = FALSE;
	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Pause
// DESC: Temporarily stop buffer playback, allowing for it's current state
//       to be restored at a later time.  Note that this method DOES NOT
//       reset the play position back to the beginning!
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet, or it
//                     is not playing, or it is already paused.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Pause() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized, that it is playing,
	// and that it is not currently paused
	if( (m_lpDSBuffer == NULL) ||
		(m_bPlaying == FALSE) ||
		(m_bPaused == TRUE) ) return ERROR_NOT_READY;

	// Attempt to stop the buffer playback
	if(FAILED( hr = m_lpDSBuffer->Stop() )) {
		SOUND_ERROR( "Failed to pause sound", hr, "CSoundEffect::Pause()" );
		return hr;
	}

	m_bPaused = TRUE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Unpause
// DESC: Restore playback from a dormant state.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet, or it
//                     is not playing, or it is not paused.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundEffect::Unpause() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized, that it is playing,
	// and that it is currently paused
	if( (m_lpDSBuffer == NULL) ||
		(m_bPlaying == FALSE) ||
		(m_bPaused == FALSE) ) return ERROR_NOT_READY;

	// Attempt to resume the buffer playback
	if( m_bLooping == TRUE ) {
		// Continue the playback in a looping fasion
		if(FAILED( hr = m_lpDSBuffer->Play(0, 0, DSBPLAY_LOOPING) )) {
			SOUND_ERROR( "Failed to unpause sound", hr, "CSoundEffect::Unpause()" );
			return hr;
		}
	}
	else {
		// Continue the playback in a one-shot fasion
		if(FAILED( hr = m_lpDSBuffer->Play(0, 0, 0) )) {
			SOUND_ERROR( "Failed to unpause sound", hr, "CSoundEffect::Unpause()" );
			return hr;
		}
	}

	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Release
// DESC: Release the stream so that it can be recycled.  This basically just
//       stops the sound, destroys the sound buffer, and resets all
//       state information.
//---------------------------------------------------------------------------//
void CSoundEffect::Release() {
	if( m_bPlaying == TRUE ) Stop();

	// Destroy old sound buffer if necessary
	if ( m_lpDSBuffer != NULL ) {
		m_lpDSBuffer->Release();
		m_lpDSBuffer = NULL;
	}

	// Reset all variables to an initial state
	m_bPlaying = FALSE;
	m_bPaused = FALSE;
	m_bLooping = FALSE;
	m_bSelfDestruct = FALSE;

	m_bLocked = FALSE;

	return;
}


//===========================================================================//
// CLASS: CSoundStream
// Desc: 
//   This class is used to play large WAV files.  Unlike the CSoundEffect
//   class, only a small portion of the sound data is loaded into the buffer
//   at a time.  The buffer is divided into four segments with notifications
//   placed at the end of each.  As soon as a notification is triggered while
//   the buffer is playing, the segment directly behind the play cursor is
//   filled with the next segment of data.  The buffer is set to looping so
//   it behaves in a circular fasion.
//
//   NOTE: For some reason, this class CANNOT handle small WAV files.  I think
//         this might be because the playback buffer is way larger than some
//         of the smaller files, so stop notifications don't work well.
//         For sounds that are only a couple hundred K, use a CSoundEffect
//         object instead.
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CSoundStream::CSoundStream() {

	// Initialize the Stream Checker thread
	m_cSTRefreshCheck = new CStreamThread();

	m_bPlaying = FALSE;
	m_bPaused = FALSE;
	m_bLooping = FALSE;
	m_bLocked = FALSE;
	m_bSelfDestruct = FALSE;

	m_fFade = 1.0f;
	m_fFadeStep = 0.0f;

	m_ulTargetFreq = 0L;
	m_lFreqStep = 0L;

	m_lTargetPan = 0L;
	m_lPanStep = 0L;

	m_fpFile = NULL;
}


//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CSoundStream::~CSoundStream() {
	Destroy();
	CSound::Destroy();
}


//---------------------------------------------------------------------------//
// NAME: Init
// DESC: Initialize the sound stream object.  This calls the base class
//       constructor, creates the events for the notification positions,
//       and starts up the checker thread.
// PARAMETERS:
//   cSCNewParent - pointer to the CSoundCore object that this sound object
//                  belongs to.
//   nNewId - integer ID for this particular sound, typically the index of
//            this object in the sound effect or stream pool.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_INVALID_THREAD_ID - could not create stream checker thread.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Init(CSoundCore *cSCNewParent, int nNewId) {
	HRESULT hr = NO_ERROR;

	if (FAILED( hr = CSound::Init( cSCNewParent, nNewId ) )) {
		SOUND_ERROR( "Failed to initialize base class", hr, "CSoundStream::Init(C,n)" );
		return hr;
	}

	// Initialize event handles
	for( int i = 0; i < STREAM_REFRESH_POINTS; i++ ) {
		m_hRefresh[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	// Start the sound effects checking thread
	m_cSTRefreshCheck->Init( this );

	if (!m_cSTRefreshCheck->create()) {
		SOUND_MESSAGE("Could not spawn checker thread in CSoundStream::Init(C,n)");
		m_cSTRefreshCheck = NULL;
		return ERROR_INVALID_THREAD_ID;
	}

	m_cSTRefreshCheck->start();

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Destroy
// DESC: Destroyer of sound streams.  Shuts down and destroys the checker
//       thread, closes the WAV file if it's still open, and destroys the
//       event handles.
//---------------------------------------------------------------------------//
void CSoundStream::Destroy() {
	// Destroy the refresh checker thread
	m_cSTRefreshCheck->shutdown();

	// Wait for the thread to shut itself down
	//while( (volatile) m_cSTRefreshCheck->IsRunning() ) {}

	// Delete the object off the heap
	if (m_cSTRefreshCheck) delete m_cSTRefreshCheck;

	if (m_fpFile != NULL) {
		try {
			// Close the file.  I don't know why but this damn thing always
			// causes an access violation exception.  So might as well give it
			// a try, but need to skip over if it doesn't work.
			fclose(m_fpFile);
		}
		catch (...) {}

		m_fpFile = NULL;
	}

	// Destroy event handles
	for( int i = 0; i < STREAM_REFRESH_POINTS; i++ ) {
		CloseHandle( m_hRefresh[i] );
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: Load
// DESC: Prepare a buffer and open the WAV file so that it's ready for
//       data reading.  The actual data isn't fed into the buffer until
//       the Play(b) method (just once) and Update() method (continuously).
// PARAMETERS:
//   cMusicName - name of the music file to be loaded.  Must be in the
//                MUSIC_PATH directory.  DO NOT include the .WAV extension
//                as this is automatically appended.
// RETURNS:
//   NO_ERROR - sound loaded successfully.
//   ERROR_FILE_NOT_FOUND - duh!
//   Otherwise - see errors returned by CreateBufferFromWav() and
//               LoadSoundData(c,l,l).
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Load( char *cMusicName ) {
	HRESULT hr = NO_ERROR;

	// Create the filename from the sound name
	char cFilename[255] = MUSIC_PATH;
	strcat( cFilename, cMusicName );
	strcat( cFilename, ".wav" );

	// Get the header information
	if ( FAILED( hr = GetWAVHeader( cFilename ) ) ) {
		SOUND_ERROR( "Could not get WAV Header", hr, "CSoundStream::Load(c)" );
		return hr;
	}

	// Open the source file
	if ( (m_fpFile = fopen(cFilename, "rb")) == NULL) {

#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, 
			"Could not open file \"%s\" in CSoundStream::Load(c).",
			cMusicName);
#endif

		return ERROR_FILE_NOT_FOUND;
	}

	// Create the sound buffer
	if ( FAILED( hr = CreateBuffer() ) ) {
		SOUND_ERROR( "Buffer creation failed", hr, "CSoundStream::Load(c)" );
		return hr;
	}

	// Refresh the sound volume
	RefreshVolume();

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: CreateBuffer
// DESC: Create the DirectSound buffer using the WAV information stored in
//       the m_swHeader structure.  Note that this requires that the
//       GetWavHeader(c) function be called before this function.  Luckily
//       this is taken care of for you by the Load(c) function.
// RETURNS:
//   NO_ERROR - buffer created successfully.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::CreateBuffer() {
	HRESULT hr = NO_ERROR;
	WAVEFORMATEX wfexFormat;
	DSBUFFERDESC dsbdBufferDesc;

	LPDIRECTSOUNDNOTIFY lpDSNotify;
	DSBPOSITIONNOTIFY dsbpNotify[STREAM_REFRESH_POINTS];

	// Set up playback format using header data
	ZeroMemory(&wfexFormat, sizeof(wfexFormat));
    wfexFormat.wFormatTag = WAVE_FORMAT_PCM; 
    wfexFormat.nChannels = m_swHeader.sChannels;
    wfexFormat.nSamplesPerSec = m_swHeader.lSampleRate; 
    wfexFormat.wBitsPerSample = m_swHeader.sBitsPerSample; 
    wfexFormat.nBlockAlign = (unsigned short) ((wfexFormat.wBitsPerSample / 8) *
		wfexFormat.nChannels); 
    wfexFormat.nAvgBytesPerSec = wfexFormat.nSamplesPerSec *
		wfexFormat.nBlockAlign; 

	// Set up buffer description using header data
	ZeroMemory(&dsbdBufferDesc, sizeof(dsbdBufferDesc));
    dsbdBufferDesc.dwSize = sizeof(DSBUFFERDESC); 
    dsbdBufferDesc.dwFlags = DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLPAN |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPOSITIONNOTIFY;

	// Allocate buffer time
    dsbdBufferDesc.dwBufferBytes = STREAM_BUFFER_BYTES;

    dsbdBufferDesc.lpwfxFormat = &wfexFormat; 

	// Create the buffer
	if ( FAILED( hr =
		m_cSCParent->m_lpDS->CreateSoundBuffer(
		&dsbdBufferDesc, &m_lpDSBuffer, NULL) ) ) {

		// Error occurred
		SOUND_ERROR( "Failed to create sound buffer", hr, "CSoundStream::CreateBuffer()" );
		return hr;
	}

	// Set file position tracking variables
	m_lDataSize = m_swHeader.lDataSize;
	m_lDataPos = sizeof(sWaveHeader);
	m_lDataLeft = m_lDataSize;

	// Setup the End of Buffer notification
	if (FAILED( hr =
		m_lpDSBuffer->QueryInterface(IID_IDirectSoundNotify8, (LPVOID*)&lpDSNotify) ) ) {
		SOUND_ERROR("Failed to query Notify interface.", hr, "CSoundStream::CreateBuffer()");
		return hr;
	}

	for(int i = 0; i < STREAM_REFRESH_POINTS; i++) {
		dsbpNotify[i].dwOffset = STREAM_BUFFER_CHUNK * (i+1) - 1;
		dsbpNotify[i].hEventNotify = m_hRefresh[i];
	}

	if (FAILED( hr =
		lpDSNotify->SetNotificationPositions(STREAM_REFRESH_POINTS, dsbpNotify) )) {

	    lpDSNotify->Release();
		SOUND_ERROR("Failed to set notification position.", hr, "CSoundStream::CreateBuffer()");
		return hr;
	}

    lpDSNotify->Release();

	// Update sound properties
	m_lpDSBuffer->GetVolume(&m_lVolume);
	m_lpDSBuffer->GetFrequency(&m_ulFrequency);
	m_lpDSBuffer->GetPan(&m_lPan);

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: LoadSoundData
// DESC: Load the actual sound data from the WAV file into the buffer which
//       is created using the CreateBufferFromWAV() method.  This method is
//       used in the Load(c) method.
// PARAMETERS:
//   lLockPos - a portion of the buffer must be locked before data can be
//              transferred in.  This indicates the starting position of the
//              locked segment.
//   lSize - this indicates the size offset from lLockPos that will be locked
//           for filling with data.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_INVALID_DATA - the lSize parameter is <= 0.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::LoadSoundData(long lLockPos, long lSize) {
	HRESULT hr = NO_ERROR;
	BYTE *bPtr1, *bPtr2;
	DWORD dwSize1, dwSize2;

	if (lSize <= 0) {
		SOUND_MESSAGE( "Sound data size cannot be zero in CSoundStream::LoadSoundData(l,l)" );
		return ERROR_INVALID_DATA;
	}

	// Lock the sound buffer at the position specified
	if ( FAILED( hr = m_lpDSBuffer->Lock(lLockPos, lSize, (void**)&bPtr1,
		&dwSize1, (void**)&bPtr2, &dwSize2, 0) ) ) {
		// Error occurred - unable to lock buffer
		SOUND_ERROR( "Unable to lock buffer", hr, "CSoundStream::LoadSoundData(l,l)" );
		return hr;
	}

	// Read in the data
	fread(bPtr1, 1, dwSize1, m_fpFile);
	if (bPtr2 != NULL)
		fread(bPtr2, 1, dwSize2, m_fpFile);

	// Unlock the buffer
	m_lpDSBuffer->Unlock(bPtr1, dwSize1, bPtr2, dwSize2);


	return hr;
}


//---------------------------------------------------------------------------//
// NAME: LoadSilence
// DESC: This is just like the LoadSoundData(l,l) method except instead of
//       filling the given buffer segment with data, we instead fill it with
//       0 values (ie. silence).  This method is typically used when a
//       non-looping stream reaches the end of it's buffer, but still has
//       a little way to go before the next notification position.  In this
//       case, we just fill up the remaining space to the next notification
//       with silence.  If we do not do this, we run the risk of playing
//       whatever data from the last pass didn't get overwritten, which will
//       sound like the music is skipping.
// PARAMETERS:
//   lLockPos - a portion of the buffer must be locked before data can be
//              transferred in.  This indicates the starting position of the
//              locked segment.
//   lSize - this indicates the size offset from lLockPos that will be locked
//           for filling with data.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_INVALID_DATA - the lSize parameter is <= 0.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::LoadSilence(long lLockPos, long lSize) {
	HRESULT hr = NO_ERROR;
	BYTE *bPtr1, *bPtr2;
	DWORD dwSize1, dwSize2;

	if (!lSize) {
		SOUND_MESSAGE( "Sound data size cannot be zero in CSoundStream::LoadSilence(l,l)" );
		return ERROR_INVALID_DATA;
	}

	// Lock the sound buffer at the position specified
	if ( FAILED( hr = m_lpDSBuffer->Lock(lLockPos, lSize, (void**)&bPtr1,
		&dwSize1, (void**)&bPtr2, &dwSize2, 0) ) ) {
		// Error occurred - unable to lock buffer
		SOUND_ERROR( "Unable to lock buffer", hr, "CSoundStream::LoadSilence(l,l)" );
		return hr;
	}

	// Fill the block with silence
	ZeroMemory(bPtr1, dwSize1);
	if( bPtr2 != NULL ) {
		ZeroMemory(bPtr2, dwSize2);
	}

	// Unlock the buffer
	m_lpDSBuffer->Unlock(bPtr1, dwSize1, bPtr2, dwSize2);

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Reset
// DESC: Reset the play position to the beginning of the buffer.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Reset() {
	HRESULT hr = NO_ERROR;
#ifdef _DEBUG
	SOUND_MESSAGE("In Reset().");
#endif

	// Ensure that the buffer has been initialized and that it is not
	// currently playing!
	if ( (m_lpDSBuffer == NULL) || (m_bPlaying == TRUE) ) return ERROR_NOT_READY;

	// Reset the file data locaters
	m_lDataPos = sizeof(sWaveHeader);
	m_lDataLeft = m_lDataSize;

	// Reset the buffer play position to the beginning
	if(FAILED( hr = m_lpDSBuffer->SetCurrentPosition(0) )) {
		// Error occurred
		SOUND_ERROR( "Failed to set play position", hr, "CSoundStream::Reset()" );
		return hr;
	}

	// Reset volume, frequency, and pan gradients
	m_fFade = 1.0f;
	m_fFadeStep = 0.0f;

	m_ulTargetFreq = 0L;
	m_lFreqStep = 0L;

	m_lTargetPan = 0L;
	m_lPanStep = 0L;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Play
// DESC: Begin buffer playback.  Note that this function calls Reset() before
//       beginning playback, so the buffer will always start playback from
//       the beginning.
// PARAMETERS:
//   bLoop - Should the sound be played looping?
//           TRUE = loop playback infinitely until manually stopped.
//           FALSE = stop buffer automatically when the end is reached.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Play( BOOL bLoop, BOOL bPause ) {
	HRESULT hr = NO_ERROR;

	// Attemp to reset the stream
	if(( hr = Reset() ) != NO_ERROR) {
		SOUND_ERROR( "Reset() failed", hr, "CSoundStream::Play(b)" );
		return hr;
	}

	// Seek to the beginning of the data
	fseek(m_fpFile, sizeof(sWaveHeader), SEEK_SET);

	// Fill the entire buffer with data to start off with
	if (FAILED( hr = LoadSoundData(0, STREAM_BUFFER_BYTES ) )) {
		SOUND_ERROR( "Could not load sound data", hr, "CSoundStream::Play(b)" );
		return hr;
	}

	// Update the current position appropriately
	m_lDataPos += STREAM_BUFFER_BYTES;
	m_lDataLeft -= STREAM_BUFFER_BYTES;


	// Set the looping flag.  If set to FALSE, the file being played does
	// not wrap, and playback stops when there is no more data.  Otherwise
	// the sound wraps and plays infinitely until manually stopped.
	m_bLooping = bLoop;

	// If the core is suspended, simply pause it so that it will be
	// played when the core is resumed.
	if ( m_cSCParent->IsSuspended() || bPause == TRUE ) {
		m_bPlaying = TRUE;
		m_bPaused = TRUE;
		return hr;
	}

	// For streams the buffer must be looping, however because we are
	// constantly streaming in new data, each pass contains the next segment
	// of the sound.  In this manner we play the entire sound.
	if (FAILED( hr = m_lpDSBuffer->Play(0, 0, DSBPLAY_LOOPING) )) {
		// Error occurred
		SOUND_ERROR( "Failed to play sound buffer", hr, "CSoundStream::Play()" );
		return hr;
	}

	m_bPlaying = TRUE;
	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Stop
// DESC: Stop buffer playback.  Note that this function calls Reset() after
//       stopping playback, so if the buffer is played again, it will
//       start from the beginning.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Stop() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized
	if( m_lpDSBuffer == NULL) return ERROR_NOT_READY;

	// Attempt to stop playback
	if ( (m_lpDSBuffer == NULL) || FAILED( hr = m_lpDSBuffer->Stop() ) ) {
		// Error occurred
		SOUND_ERROR( "Failed to stop buffer playback", hr, "CSoundEffect::Stop()" );
		return hr;
	}

	// Attempt to reset the play position to the beginning of the buffer
	if (FAILED( hr = Reset() )) {
		SOUND_ERROR( "Reset() failed", hr, "CSoundStream::Stop()" );
		return hr;
	}

	m_bPlaying = FALSE;
	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Pause
// DESC: Temporarily stop buffer playback, allowing for it's current state
//       to be restored at a later time.  Note that this method DOES NOT
//       reset the play position back to the beginning!
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet, or it
//                     is not playing, or it is already paused.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Pause() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized, that it is playing,
	// and that it is not currently paused
	if( (m_lpDSBuffer == NULL) ||
		(m_bPlaying == FALSE) ||
		(m_bPaused == TRUE) ) return ERROR_NOT_READY;

	// Attempt to stop the buffer playback
	if(FAILED( hr = m_lpDSBuffer->Stop() )) {
		SOUND_ERROR( "Failed to pause stream", hr, "CSoundStream::Pause()" );
		return hr;
	}

	m_bPaused = TRUE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Unpause
// DESC: Restore playback from a dormant state.
// RETURNS:
//   NO_ERROR - operation completed successfully.
//   ERROR_NOT_READY - the sound buffer has not been initialized yet, or it
//                     is not playing, or it is not paused.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::Unpause() {
	HRESULT hr = NO_ERROR;

	// Ensure that our sound buffer has been initialized, that it is playing,
	// and that it is currently paused
	if( (m_lpDSBuffer == NULL) ||
		(m_bPlaying == FALSE) ||
		(m_bPaused == FALSE) ) return ERROR_NOT_READY;

	// Attempt to resume the buffer playback
	if(FAILED( hr = m_lpDSBuffer->Play(0, 0, DSBPLAY_LOOPING) )) {
		SOUND_ERROR( "Failed to unpause stream", hr, "CSoundStream::Unpause()" );
		return hr;
	}

	m_bPaused = FALSE;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: RefreshVolume
// DESC: Readjust the volume based on master settings and current fade state.
// RETURNS:
//   NO_ERROR - volume successfully changed.
//   ERROR_NOT_READY - Sound buffer has not been initialized.
//   Otherwise - error code from DirectSound.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::RefreshVolume() {
	HRESULT hr = NO_ERROR;

	if( m_lpDSBuffer == NULL ) return ERROR_NOT_READY;

	long lNewVol = m_cSCParent->m_lVolume + m_lVolume;
	lNewVol += (long) ((MIN_VOLUME - lNewVol) * m_fFade);

	// Change the volume in the buffer using the master and local volumes
	if (FAILED( hr = 
		m_lpDSBuffer->SetVolume( lNewVol ) )) {
		// Error occurred
		SOUND_ERROR( "Failed to refresh volume", hr, "CSoundStream::RefreshVolume()" ); 
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: FadeIn
// DESC: Fade in buffer playback.  Note that the stream must be in a
//       *stopped* state prior to calling this method!!
// PARAMETERS:
//   bLoop - Will the stream be looping once the fade-in has completed?
//           TRUE = yes, FALSE = no.
//   fStartPerc - Initial volume for fade in, specified as a percentage
//                between 0 (mute) and 1 (full-volume).
//   fStep - Step for fading.  Each timer tick, this ammount is
//           added to the fade percentage.
// RETURNS:
//   NO_ERROR - fade initiated successfully.
//   ERROR_INVALID_DATA - fStep was 0, or fStartPerc wasn't
//                        in the range [0, 1].
//   ERROR_BAD_COMMAND - the stream is already playing.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::FadeIn(BOOL bLoop, float fStartPerc, float fStep) {
	HRESULT hr = NO_ERROR;

	// Check validity of this operation
	if ( (fStep == 0) || (fStartPerc > 1.0) || (fStartPerc < 0.0) ) {

#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, "Invalid data (step: %f, start: %f) in CSoundStream::FadeIn(b,f,f)", fStep, fStartPerc);
#endif

		return ERROR_INVALID_DATA;
	}

	// Ensure the buffer is not currently playing
	if ( (m_bPlaying == TRUE) && (m_bPaused == FALSE) ) {
		SOUND_MESSAGE( "Stream is already playing in CSoundStream::FadeIn(b,f,f)" );
		return ERROR_BAD_COMMAND;
	}

	// Ensure the step size is negative.
	if (fStep > 0) fStep *= -1;

	// Begin stream playback.  This may be from a stopped or paused state
	if( (m_bPlaying == TRUE) && (m_bPaused == TRUE) ) {
		// Unpause the file
		if(FAILED( hr = Unpause() )) {
			SOUND_ERROR( "Unpause() failed", hr, "CSoundStream::FadeIn(b,f,f)" );
			return hr;
		}
	}
	else if ( m_bPlaying == FALSE ) {
		if(FAILED( hr = Play( bLoop, TRUE ) )) {
			SOUND_ERROR( "Play() failed", hr, "CSoundStream::FadeIn(b,f,f)" );
			return hr;
		}
	}

	// Set the fade and step size.  The actual volume is updated on a timer, so
	// basically it's out of our hands after this point.
	m_fFade = fStartPerc;
	m_fFadeStep = fStep;
	RefreshVolume();

#ifdef _DEBUG
	CLog::GetLog().Write(LOG_APP, "** Fade set (f: %f, s: %f) in CSoundStream::FadeIn(b,f,f)", m_fFade, m_fFadeStep);
#endif

	if(FAILED( hr = Unpause() )) {
		SOUND_ERROR( "Unpause() failed", hr, "CSoundStream::FadeIn(b,f,f)" );
		return hr;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: FadeOut
// DESC: Fade out buffer playback.  Note that the stream must be in a
//       *playing* state, and NOT PAUSED prior to calling this method!!
//       This method automatically fades the sound all the way to
//       the minimum, so unlike the FadeIn method, you can't specify how far
//       it goes.
// PARAMETERS:
//   fStep - Step for fading.  Each timer tick, this ammount is
//           added to the fade percentage.
// RETURNS:
//   NO_ERROR - fade initiated successfully.
//   ERROR_INVALID_DATA - fStep was 0, or fStartPerc wasn't
//                        in the range [0, 1].
//   ERROR_BAD_COMMAND - the stream is already playing.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::FadeOut(float fStep) {
	HRESULT hr = NO_ERROR;

	// Check validity of fStep
	if ( (fStep == 0) ) {

#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, "Invalid data (step: %f) in CSoundStream::FadeOut(f)", fStep);
#endif

		return ERROR_INVALID_DATA;
	}

	// Ensure the buffer is not currently playing
	if ( (m_bPlaying == FALSE) || (m_bPaused == TRUE) ) {
		SOUND_MESSAGE( "Stream is not playing in CSoundStream::FadeOut(n)" );
		return ERROR_BAD_COMMAND;
	}

	// Ensure the step is positive
	if (fStep < 0) fStep *= -1;

	// Set the fade and step size.  The actual volume is updated on a timer, so
	// basically it's out of our hands after this point.  When the nFade 
	// reaches 100, the sound is automatically stopped.
	m_fFade = 0.0f;
	m_fFadeStep = fStep;
	RefreshVolume();

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: CrossFade
// DESC: Crossfade two streams (ie. Fade one in while fading the other out).
//       You don't really need to specify which is which - this function can
//       figure out what to do based on context.  Basically, whichever of the
//       two is playing is faded out, while the one that is stopped is faded
//       out.  However, if both are playing or both are stopped, then we
//       return an error.
// PARAMETERS:
//   cSStrm - Sound stream to crossfade with this one.
//   bLooping - will the faded in stream be played looping or not?
//              TRUE = yes, FALSE = no.
//   fStartPerc - Initial volume for fade in, specified as a percentage
//                between 0 (mute) and 1 (full-volume).
//   fStep - Step for fading.  Each timer tick, this ammount is
//           added to the fade percentage.
// RETURNS:
//   NO_ERROR - fade initiated successfully.
//   ERROR_INVALID_DATA - fStep was 0, or fStartPerc wasn't
//                        in the range [0, 1].
//   ERROR_BAD_COMMAND - the stream is already playing.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::CrossFade(CSoundStream *cSStrm, BOOL bLooping,
								float fStartPerc, float fStep) {
	HRESULT hr = NO_ERROR;

	// Check if we're fading this one in or out
	if ( ((m_bPlaying == FALSE) || (m_bPaused == TRUE))
		&& (cSStrm->m_bPlaying == TRUE) ) {
		// Do fade in
		if(SUCCEEDED( hr = FadeIn(bLooping, fStartPerc, fStep) ))
			cSStrm->FadeOut(fStep);
		else return hr;
	}
	else if ( (m_bPlaying == TRUE) &&
		((cSStrm->m_bPlaying == FALSE) || (cSStrm->m_bPaused == TRUE)) ) {
		// Do fade out
		if(SUCCEEDED( hr = cSStrm->FadeIn(bLooping, fStartPerc, fStep) ))
			FadeOut(fStep);
		else return hr;
	}
	else {
		SOUND_MESSAGE( "Cannot crossfade streams - either both are playing or both are stopped in CSoundStream::CrossFade(C,b,f,f)" );
		return ERROR_BAD_COMMAND;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: FadeStep
// DESC: Method that does one increment of the fade step.  This method is
//       called on a timer to produce a fading in or fading out effect.
//---------------------------------------------------------------------------//
void CSoundStream::FadeStep() {
	// No point in continuing if no fade step
	if (m_fFadeStep == 0) return;

	if(m_fFadeStep < 0) {
		m_fFade += m_fFadeStep;

		// Clamp value to 0
		if (m_fFade <= 0){
			m_fFade = 0;
			m_fFadeStep = 0;
		}

		RefreshVolume();
	}
	else {
		m_fFade += m_fFadeStep;

		// Clamp value to 1
		if (m_fFade >= 1){
			m_fFade = 1;
			m_fFadeStep = 0;

			RefreshVolume();

			// We're done fading out, pause the sound
			Pause();
		}
		else {
			RefreshVolume();
		}

	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: ResetFrequency
// DESC: Restore this stream's frequency to it's intended value.
// RETURNS:
//   NO_ERROR - restored successfully.
//   Otherwise - DirectSound error.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::ResetFrequency() {
	return SetFrequency( m_swHeader.lSampleRate );
}


//---------------------------------------------------------------------------//
// NAME: PitchBend
// DESC: Gradually change the pitch to a target frequency.
// PARAMETERS:
//   ulTarget - Target pitch for once the operation is complete.
//   lStep - Step for bending.  Each timer tick, the current frequency
//           is moved toward the target frequency by this ammount.
// RETURNS:
//   NO_ERROR - bend initiated successfully.
//   ERROR_INVALID_DATA - if the step is 0, or the target frequency is
//                        unreasonably high or low.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::PitchBend(unsigned long ulTarget, long lStep) {
	HRESULT hr = NO_ERROR;

	// Check validity of lStep and ulTarget
	if( (lStep == 0) || (ulTarget > 88400) || (ulTarget < 5525) ) {
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, "Invalid data (target: %l, step: %l) in CSoundStream::PitchBend(ul,l)", lStep, ulTarget);
#endif
		return ERROR_INVALID_DATA;
	}

	// Ensure the step is in the correct direction
	if ( m_ulFrequency > ulTarget ) {
		// Decreasing the pitch, step must be negative
		if ( lStep > 0 )
			lStep *= -1;
	}
	else {
		// Increasing the pitch, step must be positive
		if ( lStep < 0 )
			lStep *= -1;
	}

	// Set the bend aspects
	m_ulTargetFreq = ulTarget;
	m_lFreqStep = lStep;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: BendStep
// DESC: Method that does one increment of the bend step.  This method is
//       called on a timer to produce a pitch bend effect.
//---------------------------------------------------------------------------//
void CSoundStream::BendStep() {
	unsigned long ulNewFreq = 0;

	// No point in continuing if no bend step
	if (m_lFreqStep == 0) return;

	// If the pitch bend is downward...
	if(m_lFreqStep < 0) {
		// Calculate the new frequency
		ulNewFreq = m_ulFrequency + m_lFreqStep;

		// Clamp value to m_ulTargetFreq
		if (m_ulFrequency <= m_ulTargetFreq) {
			// If we've reached our target, stop bending
			ulNewFreq = m_ulTargetFreq;
			m_lFreqStep = 0;
		}

		SetFrequency( ulNewFreq );
	}
	// Otherwise, the pitch bend is upward
	else {
		// Calculate the new frequency
		ulNewFreq = m_ulFrequency + m_lFreqStep;

		// Clamp value to m_ulTargetFreq
		if (m_ulFrequency >= m_ulTargetFreq) {
			// If we've reached our target, stop bending
			ulNewFreq = m_ulTargetFreq;
			m_lFreqStep = 0;
		}

		SetFrequency( ulNewFreq );
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: PanSlide
// DESC: Gradually change the pan to a target location.
// PARAMETERS:
//   ulTarget - Target pan for once the operation is complete.
//   lStep - Step for sliding.  Each timer tick, the current pan
//           is moved toward the target pan by this ammount.
// RETURNS:
//   NO_ERROR - slide initiated successfully.
//   ERROR_INVALID_DATA - if the step is 0, or the target pan is
//                        unreasonably high or low.
//---------------------------------------------------------------------------//
HRESULT CSoundStream::PanSlide(long lTarget, long lStep) {
	HRESULT hr = NO_ERROR;

	// Check validity of lStep and ulTarget
	if( (lStep == 0) || (lTarget > MAX_PAN_RIGHT) || (lTarget < MAX_PAN_LEFT) ) {
#ifdef _DEBUG
		CLog::GetLog().Write(LOG_APP, "Invalid data (target: %l, step: %l) in CSoundStream::PanSlide(l,l)", lTarget, lStep);
#endif
		return ERROR_INVALID_DATA;
	}

	// Ensure the step is in the correct direction
	if ( m_lPan > lTarget ) {
		// Panning left, step must be negative
		if ( lStep > 0 )
			lStep *= -1;
	}
	else {
		// Panning right, step must be positive
		if ( lStep < 0 )
			lStep *= -1;
	}

	// Set the slide aspects
	m_lTargetPan = lTarget;
	m_lPanStep = lStep;

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: SlideStep
// DESC: Method that does one increment of the slide step.  This method is
//       called on a timer to produce a pan slide effect.
//---------------------------------------------------------------------------//
void CSoundStream::SlideStep() {
	long lNewPan = 0;

	// No point in continuing if no slide step
	if (m_lPanStep == 0) return;

	// If panning left...
	if(m_lPanStep < 0) {
		// Calculate the new pan
		lNewPan = m_lPan + m_lPanStep;

		// Clamp value to m_ulTargetPan
		if (m_lPan <= m_lTargetPan) {
			// If we've reached our target, stop panning.
			lNewPan = m_lTargetPan;
			m_lPanStep = 0;
		}

		SetPan( lNewPan );
	}
	// Otherwise, panning right
	else {
		// Calculate the new frequency
		lNewPan = m_lPan + m_lPanStep;

		// Clamp value to m_lTargetPan
		if (m_lPan >= m_lTargetPan) {
			// If we've reached our target, stop panning.
			lNewPan = m_lTargetPan;
			m_lPanStep = 0;
		}

		SetPan( lNewPan );
	}
	return;
}


//---------------------------------------------------------------------------//
// NAME: UpdateData
// DESC: Update the appropriate data chunk in the buffer for the event given.
//       This method is called from the checker thread every time an end of
//       chunk notification is reached, to fill the preceding chunk with
//       new data.
// PARAMETERS:
//   dwEventNum - This is the notification number that was triggered in the
//                checker thread.  This helps us to determine which chunk
//                needs to be refreshed.
// RETURNS:
//   NO_ERROR - update completed successfully.
//   ERROR_NO_DATA - sent as a notification to the checker thread that the
//                   non-looping stream should be stopped.
//   Otherwise - DirectSound error, or error from LoadSoundData(l,l) or
//               LoadSilence(l,l).
//---------------------------------------------------------------------------//
HRESULT CSoundStream::UpdateData( DWORD dwEventNum ) {
	HRESULT hr = NO_ERROR;
	long lRemPos = 0;		// Remaining position
	long lRemData = 0;		// Remaining Data	

	if ( ((m_bLooping == FALSE) && (m_lDataLeft == 0)) || m_fpFile == NULL ) {
		return ERROR_NO_DATA;
	}

	// Seek to read position in file
	fseek(m_fpFile, m_lDataPos, SEEK_SET);

	// We have two possible cases here.  Either there is enough data left to
	// fill in an entire chunk, or there's not.  This is important because
	// if we do not fill up the entire chunk, data from the last pass does
	// not get overwritten, which may cause the sound to stutter.  So we
	// must either fill the remaining space with appropriate date, or
	// simply silence.
	if(m_lDataLeft <= STREAM_BUFFER_CHUNK) {

		// This code handles the case where there is not enough data left
		// to fill an entire chunk.  Let's load the remaining data in.
		if (FAILED( hr = 
			LoadSoundData( dwEventNum * STREAM_BUFFER_CHUNK, m_lDataLeft) )) {
			SOUND_ERROR( "Could not load remaining data", hr, "CSoundStream::UpdateData(dw)" );
			return hr;
		}

		// If the stream is looping, we can simply fill the remaining space
		// of the chunk with data from the next pass in the looping sound.
		if( m_bLooping == TRUE ) {

			// Here we fill the remaining chunk space with data if needed.
			// Ensure that there is still some chunk left to fill.
			if( STREAM_BUFFER_CHUNK - m_lDataLeft != 0 ) {
				lRemPos = dwEventNum * STREAM_BUFFER_CHUNK + m_lDataLeft;
				lRemData = STREAM_BUFFER_CHUNK - m_lDataLeft;

				// Seek back to beginning of file.
				m_lDataPos = sizeof(sWaveHeader);
				fseek(m_fpFile, m_lDataPos, SEEK_SET);

				// Load data into remaining buffer space.
				if (FAILED( hr = 
					LoadSoundData( lRemPos, lRemData ) )) {
					SOUND_ERROR( "Could not load data", hr, "CSoundStream::UpdateData(dw)" );
					return hr;
				}

				// Set the locaters to indicate our new position.
				m_lDataPos += lRemData;
				m_lDataLeft = m_lDataSize - lRemData;
						
			}
			// Otherwise the sound fits in exactly, just reset to the beginning
			// of the file we're streaming the data from.
			else {
				m_lDataPos = sizeof(sWaveHeader);
				m_lDataLeft = m_lDataSize;
			}
		}
		else {
			if( STREAM_BUFFER_CHUNK - m_lDataLeft != 0 ) {
				// Here we fill the remaining chunk space with silence.
				if (FAILED( hr = 
					LoadSilence(
						dwEventNum * STREAM_BUFFER_CHUNK + m_lDataLeft,
						STREAM_BUFFER_CHUNK - m_lDataLeft ) )) {

					SOUND_ERROR( "Could not load silence", hr, "CSoundStream::UpdateData(dw)" );
					return hr;
				}
			}

			// Update the locaters so that the stream checker thread will
			// realize the stream has terminated.
			m_lDataPos += m_lDataLeft;
			m_lDataLeft = 0;
		}

	}
	else {
		// This code handles the case where there is enough data left in the
		// file we're streaming to fill a whole chunk of the buffer.
		if (FAILED( hr = 
			LoadSoundData( dwEventNum * STREAM_BUFFER_CHUNK,
			STREAM_BUFFER_CHUNK) )) {

			SOUND_ERROR( "Could not load data chunk", hr, "CSoundStream::UpdateData(dw)" );
			return hr;
		}

		// Update the locaters to reflect that we've consumed the chunk.
		m_lDataLeft -= STREAM_BUFFER_CHUNK;
		m_lDataPos  += STREAM_BUFFER_CHUNK;
	}

	return hr;
}


//---------------------------------------------------------------------------//
// NAME: Release
// DESC: Release the stream so that it can be recycled.  This basically just
//       stops the sound, destroys the sound buffer, destroys the file pointer,
//       and resets all state information.
//---------------------------------------------------------------------------//
void CSoundStream::Release() {
	if( m_bPlaying == TRUE ) Stop();

	// Destroy old sound buffer if necessary
	if ( m_lpDSBuffer != NULL ) {
		m_lpDSBuffer->Release();
		m_lpDSBuffer = NULL;
	}

	// Destroy old file pointer if necessary
	if ( m_fpFile != NULL ) {
		fclose( m_fpFile );
		m_fpFile = NULL;
	}

	// Reset all variables to an initial state
	m_bPlaying = FALSE;
	m_bPaused = FALSE;
	m_bLooping = FALSE;
	m_bSelfDestruct = FALSE;

	m_lDataSize = 0;
	m_lDataPos = 0;
	m_lDataLeft = 0;

	m_bLocked = FALSE;

	return;
}

//----------------------------------- EOF ------------------------------------//