#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "scene.h"


class CGameStateManager
{

public:
	//CGameStateManager( CScene * pkScene ) { m_kScene = pkScene; };  //J's Re-mod
	static CGameStateManager & GetGame();
	static CGameStateManager * GetGamePtr();
	
	void Initialize();
	void Shutdown();
	
	inline CScene * GetScenePtr() { return m_kScene; };
	void SetScene(CScene* newScene) { m_kScene = newScene; }; 


protected:

	CGameStateManager(){ ms_pkGame = this; };
	
	static CGameStateManager * ms_pkGame;

private:
	CScene * m_kScene;
};


#endif
//END game.h ==============================================================