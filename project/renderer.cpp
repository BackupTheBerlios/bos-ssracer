/*****************************************************************************
*
* File:  renderer.cpp
*
* BurnOut Studios - Super Street Racer
* Module:  Renderer
* Author:  Jay Javier
* Modified by:  On: 
* Date Created:  Feb 12, 2004
*
******************************************************************************
* Desc:  
*****************************************************************************/

#include "WmlVector3.h"
using namespace Wml;

// --- internal library includes --- //
#include "timer.h"
#include "renderer.h"
#include "gamestatemanager.h"
#include "settings.h"
#include "cinputconsole.h"
#include "macros.h"

// --- system includes --- //
#define STL_USING_ALL
#include "stl.h"



//-----------------------------------------------------------------------------
// static member declarations
//-----------------------------------------------------------------------------
//CD3DCamera CRenderer::m_pActiveCamera; // active camera in game
CameraType CRenderer::m_eActiveCamType = CAMERA_UNKNOWN;     // type of active cam
CD3DSettings      CRenderer::m_d3dSettings;
CD3DEnumeration   CRenderer::m_d3dEnumeration;
HRESULT CRenderer::ms_hResult                = NULL;
LPDIRECT3D9       CRenderer::m_pD3D          = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_pd3dDevice    = NULL;
//std::map<std::string, CD3DMesh *> CRenderer::m_kMeshMap;       // meshes available to this app
std::map< unsigned int, CD3DCamera * > CRenderer::m_pkCameraMap;  // cameras used by this renderer
CRenderer * CRenderer::ms_pkRenderer = NULL; 


CRenderer & CRenderer::GetRenderer() {  return *ms_pkRenderer; } 
CRenderer * CRenderer::GetRendererPtr() {  return ms_pkRenderer;  } 

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
/*CRenderer::CRenderer()
{ 
	// Gib's modification:
	ms_pkRenderer = this;
}
*/


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CRenderer::CRenderer (BOOL bFullScreen, HWND hWnd, UINT iWidth, UINT iHeight)
{
    m_hWnd = hWnd;
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_bFullScreen = bFullScreen;
    m_bConsoleDown = true; //$$$DEBUG
    GetWindowRect(hWnd, &m_rcWindow );
	ms_pkRenderer = this;
    m_bCursorVisible = false;
    m_bVisCullingEnabled = false;
    
    //Create a structure to hold the settings for our device
    ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

    // set up some utility fonts
    m_kFontMap[FONT_DEFAULT] = new CD3DFont( _T("Arial"), 12, D3DFONT_BOLD );
    m_kFontMap[FONT_SYSTEM]  = new CD3DFont( _T("System"), 12, D3DFONT_BOLD|D3DFONT_ITALIC|D3DFONT_ZENABLE );
    m_kFontMap[FONT_SMALL]   = new CD3DFont( _T("Arial"), 8 );

    // set up the skybox
    m_pSkyBox = new CD3DMesh(_T("skybox"));
    
    // set up the cameras
   	m_pkCameraMap[CAMERA_BUMPER]     = NULL;//new CD3DCamera();  // bumper camera
	m_pkCameraMap[CAMERA_CHASE]      = new CCameraChase();  // chase camera
	m_pkCameraMap[CAMERA_FREELOOK]   = new CCameraFreeLook(); // free look


	// set up default camera parameters for each main camera
    // 1 eye origin            2 look at pt      3 up vector
	// 1 field of view    2 aspect ratio  3 nearplane     4 farplane


	//--- bumper camera --- //
	//$$$TODO
	
	//--- chase camera --- //
	// eye 5 back, 3 up from objects position
	// look at car position
	// up is Y
	m_pkCameraMap[CAMERA_CHASE]->SetViewParams( &D3DXVECTOR3( 0.0f, 0.0f, 0.0f), 
                                                &D3DXVECTOR3( 0.0f, 0.0f, 1.0f) );
	// slightly wider FOV and shorter frustrum
	m_pkCameraMap[CAMERA_CHASE]->SetProjParams( D3DX_PI/5.5f, 1.0f ,1.0f ,500.0f );


	//--- free look camera --- //	
	m_pkCameraMap[CAMERA_FREELOOK]->SetViewParams( &D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 
    			                                   &D3DXVECTOR3( 0.0f, 0.0f, 0.0f) );
	// wide FOV and a large frustrum
	m_pkCameraMap[CAMERA_FREELOOK]->SetProjParams( D3DX_PI/4.0f, 1.0f, 1.0f, 1000.0f );


    // defaults to this camera
    //this->SetActiveCamera(CAMERA_FREELOOK);  //device isn't even set up yet so we can't use this funciton
    m_pActiveCamera = m_pkCameraMap[CAMERA_FREELOOK];
    m_eActiveCamType = CAMERA_FREELOOK;

    // set debugging flags
    #ifdef _DEBUG
    m_bDrawQNodeBBoxes = m_bDrawEntBBoxes = true;
    #else
    m_bDrawQNodeBBoxes = m_bDrawEntBBoxes = false;
    #endif
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CRenderer::~CRenderer()
{

}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CRenderer::Initialize()
{
    HRESULT hr;
    
    //First of all, create the main D3D object. If it is created successfully we 
    //should get a pointer to an IDirect3D8 interface.
    m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
    if(m_pD3D == NULL)
    {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "Could not initialize D3D!");
        #endif
        return E_FAIL;
    }

    D3DDISPLAYMODE d3ddm;
    if (m_bFullScreen == TRUE)
	{
        if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
        {
            return E_FAIL;
        }
	}
	else
	{
		d3ddm.Width = (UINT)m_iWidth;   // Set the screen width to the window width
		d3ddm.Height = (UINT)m_iHeight; // Set the screen height to the window height
		d3ddm.RefreshRate = 0;          // Set the refresh rate to default
		d3ddm.Format = D3DFMT_UNKNOWN; 
	}

    
    // fill in the settings for the d3d device
    m_d3dpp.Windowed = !m_bFullScreen;
    //m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    m_d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP; // flip back buffers
	m_d3dpp.BackBufferFormat = d3ddm.Format; // The color format
	m_d3dpp.BackBufferWidth  = d3ddm.Width;  // The back buffer width
	m_d3dpp.BackBufferHeight = d3ddm.Height; // The back buffer height
    m_d3dpp.BackBufferCount = 1;             //$$$DEBUG only double buffer for now
    m_d3dpp.hDeviceWindow = m_hWnd;
    m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    m_d3dpp.EnableAutoDepthStencil = TRUE;
    m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


    //Create a Direct3D device.
    if( FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_d3dpp.hDeviceWindow, 
                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
                                   &m_d3dpp, &m_pd3dDevice)) )
    {
        return E_FAIL;
    }

    // show/hide the mouse cursor
    m_pd3dDevice->ShowCursor( FALSE );//$$$DEBUGm_bCursorVisible );
    
    // init the fonts for use
    std::map< unsigned int, CD3DFont * >::iterator it;
    for ( it=m_kFontMap.begin(); it!=m_kFontMap.end(); it++)  {
        hr = it->second->InitDeviceObjects( m_pd3dDevice );
        if( FAILED( hr ) )
           return DXTRACE_ERR( "m_kFontMap[it]->InitDeviceObjects", hr );
        it->second->RestoreDeviceObjects();
    }


    char szBuf[512];
    sprintf(szBuf, "%s%s", CSettingsManager::GetSettingsManager().GetGameSetting(DIRSTATICMESH).c_str(), "skybox");
    // use the current working directory trick to make DX load the textures from the same dir
    if (!SetCurrentDirectory(szBuf))
        return E_FAIL;
    sprintf(szBuf, "%s%s", szBuf, "\\skybox.x");
    // Load the skybox
    if( FAILED( m_pSkyBox->Create( m_pd3dDevice, _T(szBuf) ) ) )
        return E_FAIL;//D3DAPPERR_MEDIANOTFOUND;
    m_pSkyBox->RestoreDeviceObjects( m_pd3dDevice );
    // set the CWD back
    if (!SetCurrentDirectory(CSettingsManager::GetSettingsManager().GetGameSetting(DIRCURRENTWORKING).c_str()))
        return E_FAIL;


    //$$$DEBUG testing lighting $$$$$$$$$$$$$$$$$$$$$$$$$$$
    D3DLIGHT9 d3dLight;


    // Initialize the structure.
    ZeroMemory(&d3dLight, sizeof(d3dLight));

    //D3DUtil_InitLight( &d3dLight );

    // Set up a white point light.
    d3dLight.Type = D3DLIGHT_POINT;
    d3dLight.Diffuse.r  = 1.0f;
    d3dLight.Diffuse.g  = 1.0f;
    d3dLight.Diffuse.b  = 1.0f;
    d3dLight.Ambient.r  = 1.0f;
    d3dLight.Ambient.g  = 1.0f;
    d3dLight.Ambient.b  = 1.0f;
    d3dLight.Specular.r = 1.0f;
    d3dLight.Specular.g = 1.0f;
    d3dLight.Specular.b = 1.0f;

    d3dLight.Position.x = 0.0f;
    d3dLight.Position.y = 500.0f;
    d3dLight.Position.z = -10.0f;//-100.0f;

    d3dLight.Attenuation0 = 1.0f; 
    d3dLight.Range        = 1000.0f;//1000.0f;

    // Set the property information for the first light.
    hr = m_pd3dDevice->SetLight(0, &d3dLight);
    if (SUCCEEDED(hr))
	    ;// Handle Success
    else
        assert(0);// Handle failure
    
    hr = m_pd3dDevice->LightEnable(0, TRUE);
        if (SUCCEEDED(hr))
	    ;// Handle Success
    else
	    assert(0);// Handle failure

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: CreateMesh()
// Desc: creates a mesh object for an entity
//      pMesh = mesh object to create D3DX mesh object for 
//      pcFileName = full path to mesh and mesh filename with .x extension
//-----------------------------------------------------------------------------
int CRenderer::CreateMesh( CD3DMesh * pMesh, char * pcFileName )
{

    FILE* fp = fopen(pcFileName, "r");

    if (!fp)  {
        CLog::GetLog().Write(LOG_GAMECONSOLE, "could not load mesh, path invalid %s", pcFileName);
        return 0;
    }

    HRESULT hr;
    if ( FAILED( hr = pMesh->Create( m_pd3dDevice, _T(pcFileName) )) )  {
	    #ifdef _DEBUG
	    CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "could not load mesh");
	    #endif
        //DXTRACE_ERR_MSGBOX( _T("could not load single mesh"), hr );
        return 0;  // Failure
	}
    pMesh->UseMeshMaterials(true);
    pMesh->RestoreDeviceObjects( m_pd3dDevice );
 
    return 1;

}


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::DisplayBackBuffer ()
{
    // The first two parameters are a source rectangle and destination rectangle
    // The third parameter sets the destination window for this presentation
    // The fourth parameter is the DirtyRegion parameter and in most cases should be set to NULL

    CheckDevice(); //$$$DEBUG

    //$$$TODO Check for frame buffer effects and apply them here

    // flip buffers
    HRESULT hr;
    hr = m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
    if ( hr == D3DERR_DEVICELOST )  {
        #ifdef _DEBUG
        CLog::GetLog().Write(LOG_APP, IDS_RENDER_ERROR, "Rendering Failed");
        #endif
        DXTRACE_ERR_MSGBOX( "m_pd3dDevice->Present( NULL, NULL, NULL, NULL ))", hr );
    }


}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
bool CRenderer::CheckDevice()
{
    switch(m_pd3dDevice->TestCooperativeLevel())					//check device
    {
    case D3DERR_DEVICELOST: 
        return false;
    case D3DERR_DEVICENOTRESET:
        if(FAILED(m_pd3dDevice->Reset(&m_d3dpp)))				//reset device
        {
            MessageBox(m_hWnd,"Reset() failed!","CheckDevice()",MB_OK);
            return false;
        }
        Initialize(); //init scene again
        return true;
    default: 
        return true;
    }
}



//-----------------------------------------------------------------------------
// Name:  RenderScene()
// Desc:  draw the scene using information from the game state
//-----------------------------------------------------------------------------
void CRenderer::RenderScene()
{
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,50,110), 1.0f, 0 );
    //m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, NULL, 1.0f, 0 );//D3DCOLOR_XRGB(0,20,50)

    InitializeState();

    // render the skybox first
    DrawSkyBox();

    InitializeState();

    m_pd3dDevice->BeginScene();  // --- begin scene drawing commands

	#ifdef _DEBUG  // show developer info
    char tMsgA[25];
	sprintf( tMsgA, "%s %s","ssracer", BOSAPPVERSION);
	m_kFontMap[FONT_SYSTEM]->DrawText( 0, 0, D3DCOLOR_ARGB(100,255,255,255), tMsgA, D3DFONT_FILTERED|D3DFONT_BOTTOM);
	#endif



    if (m_bVisCullingEnabled && CGameStateManager::GetGameStateManager().GetScenePtr()->GetQuadTree()->IsInitialized())  {
        // get visible quadtree nodes
        vector<CQuadNode *> * pvVisible = CGameStateManager::GetGameStateManager().GetScenePtr()->GetQuadTree()->GetVisibleNodesPtr();
        for (vector<CQuadNode *>::iterator it2 = pvVisible->begin();  it2 != pvVisible->end(); it2++)  {
            DrawQuadTreeNode(*it2);// render this visible nodes contents
        }
    }
    
    else {  //just draw all renderable entities

        assert(CGameStateManager::GetGameStateManager().GetScenePtr()->TEMPGetEntities());

        for (vector<CEntity *>::iterator it = CGameStateManager::GetGameStateManager().GetScenePtr()->TEMPGetEntities()->begin();
             it != CGameStateManager::GetGameStateManager().GetScenePtr()->TEMPGetEntities()->end();  it++)  
        {
            if ((*it)->getIsRenderable())
                DrawEntity(*it);
        } 
    }

    m_pd3dDevice->EndScene();  // --- end scene drawing commands     
}

/*

    assert(m_pd3dDevice);
    int iTemp=0;//$$$TEMP  should slow down the timer

//TIMERTEST:
    for(map< std::string, CD3DMesh * >::iterator it=m_kMeshMap.begin(); it!=m_kMeshMap.end(); it++ )
    {

        assert(it->second);
        CD3DMesh * pTemp = it->second;
        pMatrixStack->Push(); 
        pMatrixStack->LoadIdentity();

	    D3DMATRIX xRot, yRot, zRot;
	    // orientation
	    //vTemp = &Vector3f(0,0,0);//(*it)->GetRotate();
	    //pMatrixStack->RotateAxis(&D3DXVECTOR3(1.0f, 0.0f, 0.0f), RADIANS(vTemp->X()));
	    //pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 1.0f, 0.0f), RADIANS(vTemp->Y()));
	    //pMatrixStack->RotateAxis(&D3DXVECTOR3(0.0f, 0.0f, 1.0f), RADIANS(vTemp->Z()));
	    //pMatrixStack->RotateYawPitchRoll(vTemp->X(), vTemp->Y(), vTemp->Z());	
	    
	    // translation
	    vTemp = &Vector3f(0,0,0);//(*it)->GetTranslate();		
	    pMatrixStack->Translate(vTemp->X(), vTemp->Y(), vTemp->Z());
        //pMatrixStack->TranslateLocal(vTemp->X(), vTemp->Y(), vTemp->Z());

	    // scale
	    vTemp = &Vector3f(0.1,0.1,0.1);//(*it)->GetScale();
	    pMatrixStack->Scale(vTemp->X(), vTemp->Y(), vTemp->Z());
        //pMatrixStack->ScaleLocal(vTemp->X(), vTemp->Y(), vTemp->Z());


	    m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() );

        //actual drawing of the mesh
        assert(m_pd3dDevice);
        if ( FAILED(hr =  it->second->Render(m_pd3dDevice)) )  {
        //if ( FAILED(hr =  m_kMeshMap[(*it)->GetMesh()->m_strName]->Render(m_pd3dDevice)) )  {
		    #ifdef _DEBUG
		    //CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, IDS_RENDER_ERROR, "Mesh Drawing Failed");
            CLog::GetLog().Write(LOG_MISC|LOG_GAMECONSOLE, "Could not draw: %s", it->second->m_strName);
		    #endif
	    }
	    else {
		    #ifdef _DEBUG
		    CLog::GetLog().Write(LOG_GAMECONSOLE, "Drawing a mesh %s", it->second->m_strName);
		    #endif
        }

   	    pMatrixStack->Pop();
    }

    //$$$TEMP
    //if (iTemp < 100) {
    //    iTemp++;
    //    goto TIMERTEST;
    //}

*/

/*
LPD3DXBUFFER materialBuffer;
DWORD numMaterials; // Note: DWORD is a typedef for unsigned long
LPD3DXMESH mesh;

// Load the mesh from the specified file
hr=D3DXLoadMeshFromX("C:\\Documents and Settings\\jay.ALTRON\\My Documents\\SCHOOL\\CPSC585\\CODE\\WORKING\\project\\mercedes.x", D3DXMESH_SYSTEMMEM, 
                             m_pd3dDevice, NULL, 
                             &materialBuffer,NULL, &numMaterials, 
                             &mesh );

if (FAILED(hr))
     assert(0);//return FALSE;

D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

// Create two arrays, one for our materials and one for our textures
D3DMATERIAL9 *meshMaterials = new D3DMATERIAL9[numMaterials];
LPDIRECT3DTEXTURE9 *meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

// Loop through the material buffer extracting the data
for (DWORD i=0; i<numMaterials; i++)
{
  // Copy the material
  meshMaterials[i] = d3dxMaterials[i].MatD3D;

  // Set the ambient color for the material (D3DX does not do this)
  meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
     
  // Create the texture if it exists
  meshTextures[i] = NULL;
  if (d3dxMaterials[i].pTextureFilename)
     D3DXCreateTextureFromFile(m_pd3dDevice, d3dxMaterials[i].pTextureFilename, &meshTextures[i]);
}

// Done with the material buffer
materialBuffer->Release();


///
pMatrixStack->Push(); 
pMatrixStack->LoadIdentity();
// translation
pMatrixStack->Translate(0.0, 0.0,0.0);
// scale
pMatrixStack->Scale(0.5,0.5,0.5);
m_pd3dDevice->SetTransform( D3DTS_WORLD, pMatrixStack->GetTop() );
pMatrixStack->Pop(); 
///

for(i=0; i<numMaterials; i++ )
{
   // Set the material and texture for this subset
  m_pd3dDevice->SetMaterial(&meshMaterials[i]);
  m_pd3dDevice->SetTexture( 0,meshTextures[i] );
       
  // Draw the mesh subset
  mesh->DrawSubset( i );
}
*/



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::Cleanup()
{
    // destroy the fonts for use
    HRESULT hr;
    std::map< unsigned int, CD3DFont * >::iterator it;
    for ( it=m_kFontMap.begin(); it!=m_kFontMap.end(); it++)  {
        hr = it->second->DeleteDeviceObjects();
        if( FAILED( hr ) )
           DXTRACE_ERR_MSGBOX( "m_kFontMap::it->DeleteDeviceObjects", hr );
    }

    // destroy the skybox
    m_pSkyBox->InvalidateDeviceObjects();
    m_pSkyBox->Destroy();
    SAFE_DELETE( m_pSkyBox );


    // shutdown d3d interfaces
    if( m_pd3dDevice != NULL)
        m_pd3dDevice->Release();
    if( m_pD3D != NULL)
        m_pD3D->Release();

    //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ NEED TO DE FINAL CLEANUP TO CALL RELEASE EVERYTHING!!!!
}



//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
void CRenderer::ToggleFullScreen( int  riNewWidth, int riNewHeight )
{
    #ifdef _DEBUG
    CLog::GetLog().Write( LOG_APP, IDS_RENDER_MSG, "Toggling Fullscreen to..." );
    CLog::GetLog().Write( LOG_APP, "\tx resolution: %d y resolution %d",
                          riNewWidth, riNewHeight );
    #endif

    m_d3dpp.BackBufferWidth = (UINT)riNewWidth;  //$$$DEBUG
    m_d3dpp.BackBufferHeight = (UINT)riNewHeight;
    m_d3dpp.Windowed = !m_d3dpp.Windowed;

    if ( m_d3dpp.Windowed )
    {
        m_d3dpp.FullScreen_RefreshRateInHz = 0;
    }
    else
    {
        GetWindowRect(m_d3dpp.hDeviceWindow,&m_rcWindow);
        m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    }

    OnDeviceLost();
    ResetDevice();  

    if ( m_d3dpp.Windowed )
    {
        SetWindowPos(m_d3dpp.hDeviceWindow, 
            NULL, 
            m_rcWindow.left,
            m_rcWindow.top, 
            m_rcWindow.right - m_rcWindow.left,
            m_rcWindow.bottom - m_rcWindow.top,
            SWP_NOZORDER | SWP_DRAWFRAME | SWP_SHOWWINDOW);
    }

    //riNewWidth = m_rcWindow.right - m_rcWindow.left + 1;
    //riNewHeight = m_rcWindow.bottom - m_rcWindow.top + 1;
}


void CRenderer::ResetDevice ()
{
    ms_hResult = m_pd3dDevice->Reset(&m_d3dpp);
    
    //m_pqDefaultFont->OnResetDevice();
    InitializeState();
    //m_spkCamera->Update();
}


void CRenderer::OnDeviceLost ()
{
    //m_pqDefaultFont->OnLostDevice();
}



//-----------------------------------------------------------------------------
// Name:  IntitializeState()
// Desc:  sets up the default rendering state
//-----------------------------------------------------------------------------
void CRenderer::InitializeState ()
{
    // Set miscellaneous render states

    // z-buffering
    m_pd3dDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    m_pd3dDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
    m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

    m_pd3dDevice->SetRenderState( D3DRS_CLIPPING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
    
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
    //m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00ffffff );

    // Set up the texture 
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

    return;

}



//-----------------------------------------------------------------------------
// Name:  SetCamera()
// Desc:  set the view and projection matrices in the new camera model
// Defaults: eCameraName = CAMERA_FREELOOK
//-----------------------------------------------------------------------------
CD3DCamera * CRenderer::SetCamera( CD3DCamera* pkCamera, CameraType eCameraName)
{ 
    assert(pkCamera);
    m_pkCameraMap[eCameraName] = pkCamera; 
    
    // set the view and projection matrices for the device
    m_pd3dDevice->SetTransform( D3DTS_VIEW, pkCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, pkCamera->GetProjMatrix() );    

    // re-compute the frustrum of the new camera

    return m_pkCameraMap[eCameraName]; 
}



//-----------------------------------------------------------------------------
// Name:  GetCamera()
// Desc:  get a pointer to a camera specified by name
// Defaults: eCameraName = CAMERA_FREELOOK
//-----------------------------------------------------------------------------
CD3DCamera * CRenderer::GetCameraPtr (CameraType eCameraName)
{
    return m_pkCameraMap[eCameraName]; 
}



//-----------------------------------------------------------------------------
// Name:  Click()
// Desc:  updates any active camera positions
//-----------------------------------------------------------------------------
void CRenderer::Click()
{
    #ifdef _DEBUG
    assert(m_pActiveCamera);
    #endif    

    // get next frame from camera
    m_pActiveCamera->FrameMove(CTimer::GetTimer().GetTimeElapsed());  //m_pActiveCamera->Update();

    // set the new view matrix for the camera in the D3Ddevice
    m_pd3dDevice->SetTransform( D3DTS_VIEW, m_pActiveCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, m_pActiveCamera->GetProjMatrix() );   

}






//-----------------------------------------------------------------------------
// Name:  SetActiveCamera()
// Desc:  sets the active camera to the one specified by name
// name must be one of the enumerated types or this will fail
//-----------------------------------------------------------------------------
bool CRenderer::SetActiveCamera( CameraType eCameraName )  { 
    // check if there even exists a camera to set
    if (!m_pkCameraMap[eCameraName])
        return 0;

    // if it's a bumper cam or chase cam there has to be a vehicle to track
    if (eCameraName == CAMERA_CHASE || eCameraName == CAMERA_BUMPER)  {
        if (!CGameStateManager::GetGameStateManager().GetPlayerVehicle())  {
            CLog::GetLog().Write(LOG_GAMECONSOLE, "Renderer:  WARNING you need to set the camera to track a vehicle!");
        }
    }
    m_pActiveCamera = m_pkCameraMap[eCameraName];
    m_eActiveCamType = eCameraName; 

    // set the new view matrix for the active camera in the D3Ddevice
    m_pd3dDevice->SetTransform( D3DTS_VIEW, m_pActiveCamera->GetViewMatrix() );
    m_pd3dDevice->SetTransform( D3DTS_PROJECTION, m_pActiveCamera->GetProjMatrix() );   

    return 1;
};





//END renderer.cpp ============================================================