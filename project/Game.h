#ifndef GAME_H
#define GAME_H

#include "CScene.h"
#include "Camera.h"

#define CAMERA_BUMPER 100
#define CAMERA_CHASE  200
#define CAMERA_FREE   300  //for debugging purposes and misc use


class CGame
{

public:
	static CGame & GetGame();
	static CGame * GetGamePtr();
	void Initialize();
	void LoadMap(char * cFilename, char * cDir );
	void Shutdown();
	inline CScene * GetScenePtr() { return m_kScene; }; 

	// get a camera by name
	inline CD3DCamera * GetCameraPtr ( unsigned int uiCameraName ) 
	{ return m_pkCameraMap[uiCameraName]; }; 

protected:
	CGame(){};
	static CGame ms_Game;

private:
	static CScene * m_kScene;

	// camera models for this game
	// CAMERA_BUMPER 
	// CAMERA_CHASE  
	// CAMERA_FREE   for debugging purposes and misc use
	std::map<unsigned int, CD3DCamera *> m_pkCameraMap;
};


#endif
//END game.h ==============================================================