#include "log.h"
#include "gamestatemanager.h"


CGameStateManager * CGameStateManager::ms_pkGame = NULL;
CScene * CGameStateManager::ms_pkScene = NULL;


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
