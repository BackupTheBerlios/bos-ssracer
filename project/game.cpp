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
	char* filename;
	char test[10222] = "fjdksjfkaljlsd";

	int i=0;
	int j=1;

	for(int k=0;k<10;k++) {
		i++;
		j += 2;
	}
	
	djsflasjaskdfjs
		asdfjdkld;asfd
		asfs
		afdas

		daf
		s
		fa
		f
		d
		fa
		fa
		dfa

}


void CGame::Shutdown()
{
}


void CGame::LoadMap(char * cFilename, char * cDir )
{

}