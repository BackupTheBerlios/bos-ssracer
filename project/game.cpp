#include "log.h"
#include "game.h"
#include "camerafreelook.h"

CScene * CGame::m_kScene = NULL;


CGame & CGame::GetGame()
{
  static CGame ms_Game;  // instantiate this singleton class on first use
//  assert (this.m_Log);
  return  ms_Game;
}

//----------------------------------------------------------------------------
// GetGame ()
//   return pointer to this static object
//----------------------------------------------------------------------------
CGame * CGame::GetGamePtr()
{
  return &GetGame();
}


void CGame::Initialize()
{
	m_kScene = new CScene();

	// create cameras for game
	m_pkCameraMap[CAMERA_BUMPER] = new CD3DCamera();  // bumper camera
	
	m_pkCameraMap[CAMERA_CHASE]  = new CD3DCamera();  // chase camera

	m_pkCameraMap[CAMERA_FREE]   = new CCameraFreeLook(); // free look

	// set up default camera parameters for each main camera
    // 1 eye origin            2 look at pt      3 up vector
	// 1 field of view    2 aspect ratio  3 nearplane     4 farplane

	//--- bumper camera --- //
	//$$$TODO
	
	//--- chase camera --- //
	//$$$TODO

	//--- free look camera --- //
	// SetViewParams( starting player position, 10 metres ahead, up)
	m_pkCameraMap[CAMERA_FREE]->SetViewParams( D3DXVECTOR3(0.0f, 10.0f, -10.0f), 
				                               D3DXVECTOR3(0.0f, 0.0f, 0.0f),
									           D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	// wide FOV and a large frustrum
	m_pkCameraMap[CAMERA_FREE]->SetProjParams( D3DX_PI/4.0f, 1.0f ,1.0f ,1000.0f );
}


void CGame::Shutdown()
{
	delete m_kScene;
	// release cameras
    std::map< unsigned int, CD3DCamera * >::iterator it;
    for ( it=m_pkCameraMap.begin(); it!=m_pkCameraMap.end(); it++)  {
		delete it->second;
    }
	m_pkCameraMap.clear();
}


void CGame::LoadMap(char * cFilename, char * cDir )
{
	assert(m_kScene);
#ifdef _DEBUG
	CLog::GetLog().Write(LOG_MISC, "Loading Map: %s%s", cDir, cFilename );
#endif
	m_kScene->importScene( cFilename, cDir);
}