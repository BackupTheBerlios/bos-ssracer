#include "log.h"
#include "gamestatemanager.h"


CGameStateManager * CGameStateManager::ms_pkGame = NULL;


CGameStateManager & CGameStateManager::GetGame()
{
  return  *ms_pkGame;
}
CGameStateManager * CGameStateManager::GetGamePtr()
{
  return ms_pkGame;
}


void CGameStateManager::Initialize()
{

}

void CGameStateManager::Shutdown()
{
	m_kScene->ReleaseScene();
}
