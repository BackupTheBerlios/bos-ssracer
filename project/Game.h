#ifndef GAME_H
#define GAME_H

//#include "CScene.h"


class CGame
{

public:
	//CGame( CScene * pkScene ) { m_kScene = pkScene; };  //J's Re-mod
	static CGame & GetGame();
	static CGame * GetGamePtr();
	void Initialize();
	
	void LoadMap(char * cFilename = "debug", char * cDir = "./maps/debug/");
	void Shutdown();
	//inline CScene * GetScenePtr() { return m_kScene; }; 

	//void setScene(CScene* newScene) { m_kScene = newScene; }; 



protected:
    CGame(){ ms_pkGame = this; };

	static CGame * ms_pkGame;

private:
	//static CScene * m_kScene;
};


#endif
//END game.h ==============================================================