#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "scene.h"
#include "vehicle.h"
#include "copponentvehicle.h"
#include "inputmessage.h"


class CGameStateManager
{

public:
	CGameStateManager( CScene * pkScene ) { 
        if (!pkScene)
            ms_pkScene = new CScene();
        else
            ms_pkScene = pkScene; 

        m_playerVehicle = NULL;
        ms_pkGame = this;
    };

	static CGameStateManager & GetGameStateManager();
	static CGameStateManager * GetGameStateManagerPtr();
	
	void Initialize();
	void Shutdown();
	
	inline CScene * GetScenePtr() { return ms_pkScene; };
	void SetScene(CScene* newScene) { ms_pkScene = newScene; };
	void SetPlayerVehicle(CVehicle* param) { m_playerVehicle = param; };

	CVehicle* GetPlayerVehicle() { return m_playerVehicle; };
    //Ram's Add
    void addOpponentVehicle(COpponentVehicle* car) {m_vOpponentVehicles.push_back(car);};
    vector<COpponentVehicle*> * GetOpponents() { return &m_vOpponentVehicles; };
	void ProcessInput(CInputTaskMessage* msg);


protected:

	CGameStateManager(){  };
	
	static CGameStateManager * ms_pkGame;

private:
	CScene * ms_pkScene;
	static CVehicle* m_playerVehicle;
    //Rams add TODO must allow more than one opponent
    //setup a vector later
    static vector<COpponentVehicle*> m_vOpponentVehicles;	// Vector containing all opponents
};


#endif
//END game.h ==============================================================