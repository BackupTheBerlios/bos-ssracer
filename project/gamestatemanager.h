#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "scene.h"


class CGameStateManager
{

public:
	CGameStateManager( CScene * pkScene ) { ms_pkScene = pkScene; CGameStateManager(); };
	static CGameStateManager & GetGameStateManager();
	static CGameStateManager * GetGameStateManagerPtr();
	
	void Initialize();
	void Shutdown();
	
	inline CScene * GetScenePtr() { return ms_pkScene; };
	void SetScene(CScene* newScene) { ms_pkScene = newScene; }; 


protected:

	CGameStateManager(){ ms_pkGame = this; };
	
	static CGameStateManager * ms_pkGame;

private:
	CScene * ms_pkScene;
};


#endif
//END game.h ==============================================================