//---------------------------------------------------------------------------//
// File    : soundcore.h
// Author  : Rob Diaz-Marino
// Written : Feb 2004
//---------------------------------------------------------------------------//
#ifndef _CORE_SOUND_H_
#define _CORE_SOUND_H_

// DirectX includes
#define STL_USING_ALL
#include "stl.h"

#include <windows.h>
#include <mmsystem.h>
//#include <amstream.h>

#include <dsound.h>

// Custom Includes
#include "thread.h"
#include "kernel.h"
#include "task.h"
#include "log.h"

// Define the path where sound effect files can be found
#define SOUND_PATH "media\\sound\\"
#define MUSIC_PATH "media\\music\\"
#define MAX_SOUND_VOICES 32
#define MAX_SOUND_STREAMS 4
#define STREAM_REFRESH_POINTS 4
#define STREAM_BUFFER_BYTES 65536
#define STREAM_BUFFER_CHUNK 16384
#define FADE_TIMER_RATE 50
#define END_SILENCE_CHUNKS 3

#define MAX_VOLUME 0
#define MIN_VOLUME -10000

#define PAN_CENTER 0
#define MIN_PAN 0
#define MAX_PAN 10000
#define MAX_PAN_LEFT -10000
#define MAX_PAN_RIGHT 10000


// Macros for Sound
#define SOUNDCORE_ERROR(x, y, z) LogError(x, y, z)
#define SOUNDCORE_MESSAGE(x) LogMessage(x)
#define SOUND_ERROR(x, y, z) m_cSCParent->LogError(x, y, z)
#define SOUND_MESSAGE(x) m_cSCParent->LogMessage(x)
#define PAN_LEFT(x) -1 * x
#define PAN_RIGHT(x) x

// Forward class definitions
class CSFXThread;
class CStreamThread;
class CSoundCore;
class CSound;
class CSoundEffect;
class CSoundStream;


// Structures
//---------------------------------------------------------------------------//
// Name: sWaveHeader
// Desc: Holds header data from a .WAV file.
//---------------------------------------------------------------------------//
#pragma pack(push)
#pragma pack(1) 
typedef struct sWaveHeader {
	char cRiffSig[4];
	long lWaveformChunkSize;
	char cWaveSig[4];
	char cFormatSig[4];
	long lFormatChunkSize;
	short sFormatTag;
	short sChannels;
	long lSampleRate;
	long lBytesPerSec;
	short sBlockAlign;
	short sBitsPerSample;
	char cDataSig[4];
	long lDataSize;
} sWaveHeader;
#pragma pack(pop)


//---------------------------------------------------------------------------//
// Name: CSFXThread
// Desc: Thread for monitoring all sound effects.
//---------------------------------------------------------------------------//
class CSFXThread : public Win32Thread
{
public:
	// Constructor and Destructor
	//CSFXThread();
	~CSFXThread();

	// Public methods
	void Init(CSoundCore *cSCNewParent);
	BOOL IsRunning() { return m_bRunning; }

protected:
private:
	// Backreference to parent SoundCore object
	CSoundCore *m_cSCParent;
	BOOL m_bRunning;
	void run();
};


//---------------------------------------------------------------------------//
// Name: CStreamThread
// Desc: Thread for monitoring individual streams.
//---------------------------------------------------------------------------//
class CStreamThread : public Win32Thread
{
public:
	// Constructor and Destructor
	//CStreamThread();
	~CStreamThread();

	// Public methods
	void Init(CSoundStream *cSCNewParent);
	BOOL IsRunning() { return m_bRunning; }

protected:
private:
	// Backreference to parent SoundCore object
	CSoundStream *m_cSCParent;
	BOOL m_bRunning;
	void run();
};


//---------------------------------------------------------------------------//
// Name: CSoundCore
// Desc: Core class for manipulating sound effects and streams.
//---------------------------------------------------------------------------//
class CSoundCore
{
	// Friend classes
	friend class CSound;
	friend class CSoundEffect;
	friend class CSoundStream;
	friend class CSFXThread;
	friend class CStreamThread;

private:
	// Private Properties
	HWND m_hWnd;				// HWnd reference
	LPDIRECTSOUND8 m_lpDS;		// DirectSound object
	long m_lVolume;				// Current master volume
	CSoundEffect *m_sfx;		// Sound Effects Pool
	CSoundStream *m_stream;		// Streaming Sounds Pool
	CSFXThread *m_cSTSFXCheck;	// Sound Effects Checker Thread
	BOOL m_bSuspended;			// Indicates if the core is suspended

	// Singleton
	static CSoundCore ms_SoundCore;

	// Sound effects events
	HANDLE m_hSfxEnd[ MAX_SOUND_VOICES + 1 ];

	// Private Methods

public:
	CSoundCore ();
	~CSoundCore ();

	// Getters and Setters
	long GetMasterVolume() { return m_lVolume; }
	HRESULT SetMasterVolume(long lTargetVolume);
	BOOL IsSuspended() { return m_bSuspended; }

	// Static getters and setters
	static CSoundCore &GetSoundCore();
	static CSoundCore *GetSoundCorePtr();

	// Actions
	HRESULT Init( HWND hWndNew, long lCoopLevel );
	void Destroy();
	void Suspend();
	void Resume();

	HRESULT GetSoundEffect( const char *cSoundName, CSoundEffect **ref = NULL );
	HRESULT GetSoundStream( const char *cMusicName, CSoundStream **ref = NULL );

	void LogError( char *sErrMsg, HRESULT hr, char *sErrLoc );
	void LogMessage( char *sMsg );

protected:
};


//---------------------------------------------------------------------------//
// Name: CSound
// Desc: Base class for all sound-related objects.
//---------------------------------------------------------------------------//
class CSound
{
	// Friend classes
	friend class CSoundCore;
	friend class CSFXThread;

protected:
	// Protected Properties
	CSoundCore *m_cSCParent;

	LPDIRECTSOUNDBUFFER m_lpDSBuffer;
	sWaveHeader m_swHeader;

	// State information
	BOOL m_bPlaying;
	BOOL m_bPaused;
	BOOL m_bLooping;
	BOOL m_bLocked;
	BOOL m_bSelfDestruct;

	int m_nId;
	long m_lVolume;
	unsigned long m_ulFrequency;
	long m_lPan;

	// Protected Methods
	virtual HRESULT RefreshVolume();
	virtual HRESULT Reset() { return ERROR_NOT_SUPPORTED; }

	HRESULT GetWAVHeader( const char *cFileName );
	virtual HRESULT Load( const char *cSoundName );


public:
	// Constructor and destructor
	CSound ();
	~CSound ();

	// Initializer and Destroyer
	virtual HRESULT Init( CSoundCore *cSCNewParent, int iNewId );
	virtual void Destroy();

	// Getters and Setters
	BOOL IsPlaying() { return m_bPlaying; }
	BOOL IsPaused() { return m_bPaused; }
	BOOL IsLocked() { return m_bLocked; }
	BOOL IsLooping() { return m_bLooping; }
	BOOL IsDestruct() { return m_bSelfDestruct; }

	int GetID() { return m_nId; }
	long GetVolume() { return m_lVolume; }
	unsigned long GetFrequency() { return m_ulFrequency; }
	long GetPan() { return m_lPan; }

	void SetLooping( BOOL bLoop ) { m_bLooping = bLoop; }

	HRESULT SetVolume( float fVolPercent );
	HRESULT SetVolume( long lTargetVolume );
	HRESULT SetFrequency( unsigned long lNewFrequency );
	HRESULT SetPan( long lNewPan );
	void SetSelfDestruct() { m_bSelfDestruct = true; }

	// Actions
	float GetTrackTime();
	virtual HRESULT Play( BOOL bLoop, BOOL bPause ) { return ERROR_NOT_SUPPORTED; }
	virtual HRESULT Stop() { return ERROR_NOT_SUPPORTED; }
	virtual HRESULT Pause() { return ERROR_NOT_SUPPORTED; }
	virtual HRESULT Unpause() { return ERROR_NOT_SUPPORTED; }

	virtual void Release() {}

};


//---------------------------------------------------------------------------//
// Name: CSoundEffect
// Desc: Class for small sound effects which can be loaded entirely into
//       system memory.
//---------------------------------------------------------------------------//
class CSoundEffect : public CSound
{
	// Friend classes
	friend class CSoundCore;
	friend class CSFXThread;

private:
	// Private Properties
	HANDLE hEndEvent[1];

	// Private Methods
	HRESULT Load( const char *cSoundName );
    HRESULT CreateBufferFromWAV();
    HRESULT LoadSoundData(const char *cFilename, long lLockPos, long lSize);
	HRESULT Reset();

public:
	// Constructor and destructor
	CSoundEffect ();
	~CSoundEffect ();

	// Initializer and Destroyer
	HRESULT Init( CSoundCore *cSCNewParent, int iNewId );
	void Destroy();

	// Actions
	HRESULT Play( BOOL bLoop, BOOL bPause );
	HRESULT Stop();
	HRESULT Pause();
	HRESULT Unpause();

	void Release();

protected:
};


//---------------------------------------------------------------------------//
// Name: CSoundStream
// Desc: Class for large sound effects which cannot be loaded entirely into
//       system memory, but instead must be steamed from disk.
//---------------------------------------------------------------------------//
class CSoundStream : public CSound
{
	// Friend classes
	friend class CSoundCore;
	friend class CSFXThread;
	friend class CStreamThread;

private:
	// Private Properties
	FILE *m_fpFile;
	CStreamThread *m_cSTRefreshCheck;	// Buffer Refresh Checker Thread
	long m_lDataSize, m_lDataPos, m_lDataLeft;	// Used for managing stream file
	float m_fFade;				// Current fade % - 0 = Normal Volume, 1 = Muted
	float m_fFadeStep;			// Step size for fade in/out
	unsigned long m_ulTargetFreq;	// Target frequencies for pitch bend
	long m_lFreqStep;			// Step size for pitch bend
	long m_lTargetPan;			// Target pan for pan slide
	long m_lPanStep;			// Step size for pan slide
	int m_nSilenceChunks;		// Number of silence chunks loaded
	int m_nNumLoops;			// Number of times this stream has looped

	// Private Methods
	HRESULT Load( const char *cSoundName );
    HRESULT CreateBuffer();
    HRESULT LoadSoundData(long lLockPos, long lSize);
	HRESULT LoadSilence(long lLockPos, long lSize);
	HRESULT UpdateData( DWORD dwEventNum );
	HRESULT RefreshVolume();
	HRESULT Reset();

	void FadeStep();
	void BendStep();
	void SlideStep();

	// Buffer refresh markers
	HANDLE m_hRefresh[STREAM_REFRESH_POINTS];

public:
	// Constructor and destructor
	CSoundStream ();
	~CSoundStream ();

	// Initializer and Destroyer
	HRESULT Init( CSoundCore *cSCNewParent, int iNewId );
	void Destroy();

	// Getters and Setters
	float GetTimeLeft() { return (float) m_lDataLeft / (float) m_swHeader.lBytesPerSec; }
	float GetTimePlayed() { return (float) m_lDataPos / (float) m_swHeader.lBytesPerSec; }
	bool IsFading() { return m_fFadeStep != 0.0f ? true : false; }
	bool IsBending() { return m_lFreqStep != 0.0f ? true : false; }
	bool IsSliding() { return m_lPanStep != 0.0f ? true : false; }
	int GetNumLoops() { return m_nNumLoops; }
	int GetNumSilenceChunks() { return m_nSilenceChunks; }

	// Actions
	HRESULT Play( BOOL bLoop, BOOL bPause );
	HRESULT Stop();
	HRESULT Pause();
	HRESULT Unpause();

	// Volume fades
	HRESULT FadeIn(BOOL bLooping, float fStartPerc, float fStep);
	HRESULT FadeOut(float fStep);
	HRESULT CrossFade(CSoundStream *cSStrm, BOOL bLooping, float fStartPerc, float fStep);

	// Pitch bends
	HRESULT ResetFrequency();
	HRESULT PitchBend(unsigned long ulTarget, long lStep);

	// Pan slides
	HRESULT PanSlide(long ulTarget, long lStep);

	void Release();

protected:
};


//----------------------------------- EOF ------------------------------------//
#endif
