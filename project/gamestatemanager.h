#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "scene.h"
#include "vehicle.h"


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
	void SetPlayerVehicle(CVehicle* param) { m_playerVehicle = param; };

	CVehicle* GetPlayerVehicle() { return m_playerVehicle; };


protected:

	CGameStateManager(){ ms_pkGame = this; };
	
	static CGameStateManager * ms_pkGame;

private:
	CScene * ms_pkScene;
	CVehicle* m_playerVehicle;
};


#endif
//END game.h ==============================================================