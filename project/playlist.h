//---------------------------------------------------------------------------//
// File    : playlist.h
// Author  : Rob Diaz-Marino
// Written : Mar 2004
//---------------------------------------------------------------------------//
#ifndef _PLAYLIST_H_
#define _PLAYLIST_H_

// STL includes
#define STL_USING_ALL
#include "stl.h"
#include <vector>
#include <string>
#include <fstream>

// #defines
#define PLAYLIST_FADETIME 5
#define FADE_TRANSITION 0
#define CROSSFADE_TRANSITION 1

//forward class definitions
class CPlayList;


//---------------------------------------------------------------------------//
// Name: CPlayList
// Desc: Stores a list of music files
//---------------------------------------------------------------------------//
class CPlayList
{
private:
	// List of all files
	vector<std::string> m_vPlayEntry;

	// Stream data
	CSoundStream *m_cStrm;

	// Control data
	bool m_bPlaying;
	bool m_bPaused;
	int m_nCurrentPos;
	bool m_bAutoAdvance;
	bool m_bAutoRepeat;
	float m_fVolume;
	int m_nTransType;
	bool m_bPlayNext;

protected:

public:
	CPlayList();
	~CPlayList();

	// Loading track information
	void Load( char* cListName );
	void AddTrack( char* cTrackName );

	// Manual play controls
	void Play( float fVol, bool bAutoRepeat, bool bAutoAdvance );
	void Stop();
	void Pause();
	void Unpause();
	void Next();
	void Prev();
	void Shuffle();
	void Clear();

	// Status update
	void Update();

	// Properties
	bool IsPlaying() { return m_bPlaying; }
	bool IsPaused() { return m_bPaused; }
	bool IsAutoAdvance() { return m_bAutoAdvance; }
	bool IsAutoRepeat() { return m_bAutoRepeat; }
	int GetTrackNum() { return m_nCurrentPos; }
	void SetTrackNum();

};


//----------------------------------- EOF ------------------------------------//
#endif