#include "log.h"
#include "game.h"


CGame * CGame::ms_pkGame			 = NULL;


CGame & CGame::GetGame()
{
  return  *ms_pkGame;
}
CGame * CGame::GetGamePtr()
{
  return ms_pkGame;
}


void CGame::Initialize()
{

}


void CGame::Shutdown()
{
}


void CGame::LoadMap(char * cFilename, char * cDir )
{

}