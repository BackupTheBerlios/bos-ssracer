#include "log.h"
#include "gamestatemanager.h"
#include "camera.h"
#include "camerafreelook.h"
#include "input.h"
#include "macros.h"

CVehicle * CGameStateManager::m_playerVehicle = NULL;
CGameStateManager * CGameStateManager::ms_pkGame = NULL;

//Rams add
vector<COpponentVehicle*> CGameStateManager::m_vOpponentVehicles;	// Vector containing all opponents

CGameStateManager & CGameStateManager::GetGameStateManager()
{
  return  *ms_pkGame;
}
CGameStateManager * CGameStateManager::GetGameStateManagerPtr()
{
  return ms_pkGame;
}


void CGameStateManager::Initialize()
{
}

void CGameStateManager::Shutdown()
{
	ms_pkScene->ReleaseScene();
}

void CGameStateManager::ProcessInput(CInputTaskMessage* msg)
{
	if(m_playerVehicle) {
		switch(msg->m_keyValue)
		{
			CLog::GetLog().Write(LOG_GAMECONSOLE, "GameState got key: %x", msg->m_keyValue);
			
		case GAME_NUMPAD8:
		case GAME_BUTTON0:
			if(msg->m_keyDown) {
				m_playerVehicle->SetGas(true);
			}
			else {
				m_playerVehicle->SetGas(false);
			}
			break;

		case GAME_NUMPAD5:
		case GAME_BUTTON2:
			if(msg->m_keyDown) {
				m_playerVehicle->SetBrake(true);
			}
			else {
				m_playerVehicle->SetBrake(false);
			}
			break;

		case GAME_NUMPAD4:
		case GAME_LEFT:
			if(msg->m_keyDown) {
				m_playerVehicle->SetLTurn(true);
			}
			else {
				m_playerVehicle->SetLTurn(false);
			}
			break;

		case GAME_NUMPAD6:
		case GAME_RIGHT:
			if(msg->m_keyDown) {
				m_playerVehicle->SetRTurn(true);
			}
			else {
				m_playerVehicle->SetRTurn(false);
			}
			break;
		}

	}   
}
