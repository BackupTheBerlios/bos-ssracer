#include "log.h"
#include "gamestatemanager.h"


CGameStateManager * CGameStateManager::ms_pkGame = NULL;


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
	m_kScene->ReleaseScene();
}
