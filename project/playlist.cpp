//---------------------------------------------------------------------------//
// File    : playlist.cpp
// Author  : Rob Diaz-Marino
// Written : Mar 2004
//---------------------------------------------------------------------------//
// System Includes
#include <time.h>

// Custom Includes
#include "soundcore.h"
#include "playlist.h"


//===========================================================================//
// CLASS: CPlayList
// Desc: 
//   
//===========================================================================//

//---------------------------------------------------------------------------//
// Constructor
//---------------------------------------------------------------------------//
CPlayList::CPlayList() {
	m_bPlaying = false;
	m_bAutoAdvance = false;
	m_bAutoRepeat = false;
	m_nCurrentPos = 0;
	m_fVolume = 0.0f;
	m_nTransType = FADE_TRANSITION;
	m_bPlayNext = false;

	m_cStrm = NULL;

	// Seed the random number generator
	srand( time(NULL) );

	return;
}

//---------------------------------------------------------------------------//
// Destructor
//---------------------------------------------------------------------------//
CPlayList::~CPlayList() {
	// Release the sound stream if necessary
	if ( m_cStrm != NULL ) {
		m_cStrm->Release();
		m_cStrm = NULL;
	}

	m_bPlaying = false;
	m_bAutoRepeat = false;
	m_bAutoAdvance = false;

	return;
}


//---------------------------------------------------------------------------//
// NAME: Load
// DESC: Load playlist from a file
//---------------------------------------------------------------------------//
void CPlayList::Load( char* cListName ) {
	// Complete the path and filename
	std::string sListName = cListName;
	sListName = MUSIC_PATH + sListName + ".spl";

	// Open the input stream
    std::ifstream ifsListIn( sListName.c_str() );
	if ( !ifsListIn ) {
#ifdef _DEBUG
		CLog::GetLog().Write( LOG_GAMECONSOLE, "Cannot open playlist \"%s\"!", cListName );
#endif
		return;
	}

	// Read in the list
	while( !ifsListIn.eof() ) {
		std::string fName;
		ifsListIn >> fName;

		if (fName != "") {
			m_vPlayEntry.push_back( fName );
			CLog::GetLog().Write( LOG_GAMECONSOLE, "Loaded in \"%s\" to playlist.", fName.c_str() );
		}
	}

	// Close the input stream
	ifsListIn.close();

	return;
}


//---------------------------------------------------------------------------//
// NAME: AddTrack
// DESC: Manually add a track to the playlist
//---------------------------------------------------------------------------//
void CPlayList::AddTrack( char* cTrackName ) {
	std::string sName = cTrackName;
	m_vPlayEntry.push_back( sName );

#ifdef _DEBUG
	CLog::GetLog().Write( LOG_GAMECONSOLE, "Playlist: Added \"%s\" as track %d.", cTrackName, m_vPlayEntry.size() );
#endif

	return;
}


//---------------------------------------------------------------------------//
// NAME: Play
// DESC: Begins playing the playlist.
//---------------------------------------------------------------------------//
void CPlayList::Play( float fVol, bool bAutoRepeat, bool bAutoAdvance ) {
	HRESULT hr = ERROR_OUT_OF_STRUCTURES;
	int nFailed = 0;

	// Ensure the sound stream object is free
	if ( m_cStrm != NULL ) {
		m_cStrm->Release();
		m_cStrm = NULL;
	}

	// Ensure the current track is valid!
	if ( (int) m_vPlayEntry.size() <= m_nCurrentPos ) {
#ifdef _DEBUG
		CLog::GetLog().Write( LOG_GAMECONSOLE, "Playlist: Invalid track number %d.  List contains %d tracks.", m_nCurrentPos, m_vPlayEntry.size() );
#endif
		return;
	}

	// Loop until either we find a valid track, or we get back to where we started.
	while ( (nFailed < (int) m_vPlayEntry.size()) && (hr != NO_ERROR) ) {
		hr = CSoundCore::GetSoundCore().GetSoundStream( m_vPlayEntry[ m_nCurrentPos ].c_str(), &m_cStrm );

		if ( hr != NO_ERROR ) {
#ifdef _DEBUG
			CLog::GetLog().Write( LOG_GAMECONSOLE, "Playlist: Could not load track \"%s\".", m_vPlayEntry[ m_nCurrentPos ].c_str() );
#endif
			// Free the stream
			m_cStrm->Release();

			// Advance the track number
			m_nCurrentPos = (m_nCurrentPos + 1) % m_vPlayEntry.size();
			nFailed++;
		}
	}

	// All tracks in playlist failed!!
	if (nFailed == (int) m_vPlayEntry.size()) {
#ifdef _DEBUG
		CLog::GetLog().Write( LOG_GAMECONSOLE, "Playlist: Could not find ANY files to play.  Screw you guys, I'm going home." );
#endif
		Stop();
		return;
	}

	// Assign play properties
	m_bAutoRepeat = bAutoRepeat;
	m_bAutoAdvance = bAutoAdvance;
	m_fVolume = fVol;
	m_bPlaying = true;

	// Start the stream playback
	m_cStrm->SetVolume( m_fVolume );
	m_cStrm->Play( false, false );

	return;
}


//---------------------------------------------------------------------------//
// NAME: Play
// DESC: Begins playing the playlist.
//---------------------------------------------------------------------------//
void CPlayList::Stop() {
	if (m_cStrm == NULL) return;

	// Stop the current sound stream
	m_cStrm->Stop();

	// Release the stream
	m_cStrm->Release();

	// Reset the play position
	m_nCurrentPos = 0;
	m_bPlaying = false;

	return;
}


//---------------------------------------------------------------------------//
// NAME: Pause
// DESC: Begins playing the playlist.
//---------------------------------------------------------------------------//
void CPlayList::Pause() {
	if (m_cStrm == NULL) return;
	if (m_bPaused == true) return;

	// Pause the current sound stream
	m_cStrm->Pause();

	m_bPaused = true;

	return;
}


//---------------------------------------------------------------------------//
// NAME: Unpause
// DESC: Begins playing the playlist.
//---------------------------------------------------------------------------//
void CPlayList::Unpause() {
	if (m_cStrm == NULL) return;
	if (m_bPaused == false) return;

	// Pause the current sound stream
	m_cStrm->Unpause();

	m_bPaused = false;

	return;
}


//---------------------------------------------------------------------------//
// NAME: Update
// DESC: Refresh list status and perform automated functions such as
//       advancing the track.
//---------------------------------------------------------------------------//
void CPlayList::Update() {
	// Ensure the current stream is valid
	if ( m_cStrm == NULL ) return;

	float fTimeLeft = m_cStrm->GetTimeLeft();

	// Has the current track ended?
	if ( (m_bPlaying == true) && (m_cStrm->IsPlaying() == false) ) {
		// Do we advance to the next track?
		if ( m_bAutoAdvance == false ) {
			// No, stop the playlist
			Stop();
		}
		else {
			// Yes, go to next track
			Next();
		}
	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: Next
// DESC: Advance the playlist to the next track.
//---------------------------------------------------------------------------//
void CPlayList::Next() {
	// Advance the track number
	m_nCurrentPos = (m_nCurrentPos + 1) % m_vPlayEntry.size();

	// Start the next track playing
	Play( m_fVolume, m_bAutoRepeat, m_bAutoAdvance );

/*
	float fStep = 0.0f;
	// Calculate an appropriate fadestep such that the volume reaches 0 at
	// approximately the time the song ends.
	fStep = m_fVolume / (float) PLAYLIST_FADETIME;

	// Handle different transition types.
	switch ( m_nTransType ) {
	case CROSSFADE_TRANSITION:
		break;

	default: // FADE_TRANSITION
		m_cStrm->FadeOut( fStep );
		break;
	}
*/

	return;
}


//---------------------------------------------------------------------------//
// NAME: Prev
// DESC: Regress the playlist to the previous track.
//---------------------------------------------------------------------------//
void CPlayList::Prev() {
	// Regress the track number
	m_nCurrentPos = m_nCurrentPos - 1;
	if (m_nCurrentPos < 0) m_nCurrentPos += m_vPlayEntry.size();

	// Start the previous track playing
	Play( m_fVolume, m_bAutoRepeat, m_bAutoAdvance );

	return;
}


//---------------------------------------------------------------------------//
// NAME: Shuffle
// DESC: Shuffle the playlist so that tracks play in a random order.
//---------------------------------------------------------------------------//
void CPlayList::Shuffle() {
	int i = 0, iRnd = 0;
	std::string sTmp;

	for( i = 0; i < (int) m_vPlayEntry.size(); i++ ) {
		// Select a random position to swap with
		iRnd = rand() % m_vPlayEntry.size();

		// Swap the file names
		sTmp = m_vPlayEntry[iRnd];
		m_vPlayEntry[iRnd] = m_vPlayEntry[i];
		m_vPlayEntry[i] = sTmp;

	}

	return;
}


//---------------------------------------------------------------------------//
// NAME: Clear
// DESC: Clean out the entire playlist
//---------------------------------------------------------------------------//
void CPlayList::Clear() {
	// Stop the playlist if it is currently playing
	if (m_bPlaying == true) {
		Stop();
	}

	// Clear the vector
	m_vPlayEntry.clear();

	return;
}