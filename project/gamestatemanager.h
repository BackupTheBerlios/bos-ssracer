#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "scene.h"


class CGameStateManager
{

public:
	CGameStateManager( CScene * pkScene ) { m_kScene = pkScene; CGameStateManager(); };  //J's Re-mod
	static CGameStateManager & GetGameStateManager();
	static CGameStateManager * GetGameStateManagerPtr();
	
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