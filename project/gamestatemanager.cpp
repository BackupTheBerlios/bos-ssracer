#include "log.h"
#include "gamestatemanager.h"
#include "camera.h"
#include "camerafreelook.h"
#include "macros.h"


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
	/*
	//if (!m_kScene)
	//	m_kScene = new CScene();

	// create cameras for game
	//m_pkCameraMap[CAMERA_BUMPER] = NULL;//new CD3DCamera();  // bumper camera
	
	//m_pkCameraMap[CAMERA_CHASE]  = new CCameraChase();  // chase camera

	m_pkCameraMap[CAMERA_FREE]   = new CCameraFreeLook(); // free look

	// set up default camera parameters for each main camera
    // 1 eye origin            2 look at pt      3 up vector
	// 1 field of view    2 aspect ratio  3 nearplane     4 farplane


	//--- bumper camera --- //
	//$$$TODO
	
	//--- chase camera --- //
	// eye 5 back, 3 up from objects position
	// look at car position
	// up is Y
	//m_pkCameraMap[CAMERA_CHASE]->SetViewParams( &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
				                                &D3DXVECTOR3(0.0f, 0.0f, 1.0f));,
									            D3DXVECTOR3(0.0f, 1.0f, 0.0f) );
	// shorter FOV shorter frustrum
	//m_pkCameraMap[CAMERA_CHASE]->SetProjParams( D3DX_PI/3.0f, 1.0f ,1.0f ,100.0f );


	//--- free look camera --- //	
	// HAVE TO FIX UPDATE FUNCTION TO USE PRESET VIEW MATRIX
	m_pkCameraMap[CAMERA_FREE]->SetViewParams( &D3DXVECTOR3(0.0f, 0.0f, -1.0f), 
				                               &D3DXVECTOR3(0.0f, 0.0f, 0.0f));//,
									           //D3DXVECTOR3(0.0f, 1.0f, 0.0f) );

	// wide FOV and a large frustrum
	m_pkCameraMap[CAMERA_FREE]->SetProjParams( D3DX_PI/4.0f, 1.0f ,1.0f ,1000.0f );
	//m_pkCameraMap[CAMERA_FREE]->m_trans = D3DXVECTOR3(0.0f, 10.0f, -10.0f);
	//m_pkCameraMap[CAMERA_FREE]->m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

    // defaults to this camera
    m_pkActiveCamera = m_pkCameraMap[CAMERA_FREE];

  */
}

void CGameStateManager::Shutdown()
{
	ms_pkScene->ReleaseScene();
}
